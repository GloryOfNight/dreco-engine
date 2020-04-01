#include "game_board.hxx"

#include "../game_instance.hxx"
#include "core/audio_manager.hxx"
#include "core/resource_manager.hxx"
#include "game_objects/game_world.hxx"
#include "gem.hxx"
#include "math/transform.hxx"
#include "renderer/shader_properties.hxx"
#include "renderer/mesh_data.hxx"
#include "utils/file_utils.hxx"
#include "core/engine.hxx"
#include "renderer/opengles2_renderer.hxx"

#include <string>

game_board::game_board(dreco::game_world* _w) : game_object(_w)
{
}

game_board::~game_board()
{
	for (uint8_t w = 0; w < BOARD_WIDTH; ++w)
	{
		for (uint8_t h = 0; h < BOARD_HEIGHT; ++h)
		{
			delete cells[w][h];
		}
	}
}

void game_board::Begin()
{
	game_object::Begin();
	gi = dynamic_cast<game_instance*>(GetWorld()->GetGameInstance());
	CreateBoard();

	dreco::resource_manager* res_man = GetGameInstance()->GetResourceManager();
	res_man->LoadResource("res/audio/matchsound.wav", dreco::resource_type::AUDIO);
	res_man->LoadResource("res/music/wakfumusic.ogg", dreco::resource_type::MUSIC);

	// start play infinite looped music
	// dreco::music* m =
	//	dynamic_cast<dreco::music*>(res_man->GetResource("res/music/wakfumusic.ogg"));
	// GetGameInstance()->GetAudioManager()->PlayMusic(*m);
}

void game_board::Tick(const float& DeltaTime)
{
	gem* selected_gem = dynamic_cast<gem*>(gi->GetSelectedObject());
	const bool is_mouse_down = gi->GetIsMouseButtonDown();

	if (is_mouse_down && selected_gem && !selected_gem->GetIsSelected())
	{
		if (selected_gems.empty())
		{
			selected_gems.push_back(selected_gem);
			selected_gem->SetIsSelected(true);
		}
		else
		{
			gem* last_selected_gem = selected_gems.back();
			dreco::int_vec2 pos_offset = last_selected_gem->GetCell()->GetPosition() -
										 selected_gem->GetCell()->GetPosition();

			const bool can_be_selected = (pos_offset.x <= 1 && pos_offset.x >= -1) &&
										 (pos_offset.y <= 1 && pos_offset.y >= -1);

			if (last_selected_gem != selected_gem &&
				last_selected_gem->GetGemType() == selected_gem->GetGemType() &&
				can_be_selected)
			{
				selected_gems.push_back(selected_gem);
				selected_gem->SetIsSelected(true);
			}
		}
	}
	else if (!is_mouse_down && !selected_gems.empty())
	{
		const bool can_be_collected = selected_gems.size() > 2;
		for (auto gem : selected_gems)
		{
			if (can_be_collected)
			{
				gem->OnCollected();
				collected_gems.push_back(gem);
				++reciently_removed_gems_count;
			}
			else
			{
				gem->SetIsSelected(false);
			}
		}
		selected_gems.clear();
	}

	if (collected_gems.size() > 0)
	{
		for (uint8_t w = 0; w < BOARD_HEIGHT; ++w)
		{
			board_cell* cell_to_spawn_in = cells[w][BOARD_HEIGHT - 1];
			if (cell_to_spawn_in->GetCellState() == cell_states::empty &&
				collected_gems.size() > 0)
			{
				gem* gem_to_spawn = collected_gems.back();
				collected_gems.pop_back();

				gem_to_spawn->SetGemType(static_cast<gem_types>(rand() % 5));
				gem_to_spawn->SetCurrentCell(cell_to_spawn_in);
				cell_to_spawn_in->SetCurrentGem(gem_to_spawn);
				auto t = gem_to_spawn->GetTransform();
				t.translation = cell_to_spawn_in->translation;
				t.translation.y += BOARD_TILE_SPACE;
				gem_to_spawn->SetTransform(t);
				gem_to_spawn->OnReturn();
			}
		}
	}

	// simple login for sound playing
	if (reciently_removed_gems_count > 0)
	{
		reciently_removed_gems_timer -= DeltaTime;

		if (reciently_removed_gems_timer <= 0.0f)
		{
			dreco::audio* a = dynamic_cast<dreco::audio*>(
				GetWorld()->GetGameInstance()->GetResourceManager()->GetResource(
					"res/audio/matchsound.wav"));
			GetWorld()->GetGameInstance()->GetAudioManager()->PlayAudio(*a, -1, 0);

			reciently_removed_gems_timer = 0.1f;
			--reciently_removed_gems_count;
		}
	}
}

void game_board::CreateBoard()
{
	char* vert_src;
	dreco::file_utils::LoadSourceFromFile("res/shaders/default_shader.vert", &vert_src);
	char* frag_src;
	dreco::file_utils::LoadSourceFromFile("res/shaders/default_shader.frag", &frag_src);
	const dreco::shader_properties shader_prop(vert_src, frag_src);

	dreco::mesh_data* mesh = dreco::mesh_data::CreateSpritePlane();
	GetGameInstance()->GetEngine()->GetRenderer()->AddMeshData(mesh);

	LoadGemTextures();

	dreco::transform gem_trans = dreco::transform();
	gem_trans.scale = dreco::vec2(0.15f, 0.15f);

	const uint16_t TOTAL_GEMS = BOARD_WIDTH * BOARD_HEIGHT;

	for (uint8_t i = 0; i < TOTAL_GEMS; ++i)
	{
		const uint8_t x = i >= BOARD_WIDTH ? i - ((i / BOARD_WIDTH) * BOARD_WIDTH) : i;
		const uint8_t y = i >= BOARD_WIDTH ? i / BOARD_WIDTH : 0;
		cells[x][y] = new board_cell(*this, dreco::int_vec2(x, y));

		gem* cur_gem = new gem(GetWorld(), mesh, shader_prop, *this);
		gems[i] = cur_gem;

		const char name[]{'g', 'e', 'm', '_', static_cast<char>(i)};
		GetWorld()->RegisterObject(&name[0], *cur_gem);
		gem_trans.translation =
			dreco::vec2(BOARD_TILE_SPACE * x - BOARD_CENTER_OFFSET_WIDTH,
				BOARD_TILE_SPACE * y - BOARD_CENTER_OFFSET_HEIGHT);

		cur_gem->SetTransform(gem_trans);
		cur_gem->SetGemType(static_cast<gem_types>(rand() % 5));
		cur_gem->SetCurrentCell(cells[x][y]);
		cells[x][y]->SetCurrentGem(cur_gem);
	}
}

dreco::texture* game_board::GetGemTexture(const gem_types& _t) const
{
	dreco::resource_manager* res_man = GetGameInstance()->GetResourceManager();
	std::string tex_path = "res/textures/";

	switch (_t)
	{
		case gem_types::blue:
			tex_path.append("gem_blue.png");
			break;
		case gem_types::red:
			tex_path.append("gem_red.png");
			break;
		case gem_types::yellow:
			tex_path.append("gem_yellow.png");
			break;
		case gem_types::green:
			tex_path.append("gem_green.png");
			break;
		case gem_types::purple:
			tex_path.append("gem_purple.png");
			break;
	}

	auto res = res_man->GetResource(tex_path.c_str());

	return dynamic_cast<dreco::texture*>(res);
}

board_cell* game_board::GetCellFromPosition(const dreco::int_vec2& _p) const
{
	return cells[_p.x][_p.y];
}

void game_board::LoadGemTextures()
{
	dreco::resource_manager* res_man = GetGameInstance()->GetResourceManager();

	res_man->LoadResource("res/textures/gem_red.png", dreco::resource_type::TEXTURE);
	res_man->LoadResource("res/textures/gem_blue.png", dreco::resource_type::TEXTURE);
	res_man->LoadResource("res/textures/gem_green.png", dreco::resource_type::TEXTURE);
	res_man->LoadResource("res/textures/gem_purple.png", dreco::resource_type::TEXTURE);
	res_man->LoadResource("res/textures/gem_yellow.png", dreco::resource_type::TEXTURE);
}
