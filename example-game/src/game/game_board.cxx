#include "game_board.hxx"

#include "../game_instance.hxx"
#include "game_objects/game_world.hxx"
#include "gem.hxx"
#include "math/transform.hxx"
#include "renderer/shader_properties.hxx"
#include "renderer/vertex_properties.hxx"
#include "utils/file_utils.hxx"

#include <string>

game_board::game_board()
{
}

game_board::~game_board()
{
	for (auto t : gem_textures)
	{
		delete t.second;
	}

	for (uint8_t w = 0; w < BOARD_WIDTH; ++w)
	{
		for (uint8_t h = 0; h < BOARD_HEIGHT; ++h)
		{
			delete cells[w][h];
		}
	}
}

void game_board::Init(dreco::game_world& _w)
{
	game_object::Init(_w);
	gi = dynamic_cast<game_instance*>(GetWorld()->GetGameInstance());
	CreateBoard();
}

void game_board::Tick(const float& DeltaTime)
{
	gem* selected_gem = dynamic_cast<gem*>(gi->GetSelectedObject());
	const bool is_mouse_down = gi->GetIsMouseButtonDown();

	if (is_mouse_down && selected_gem && !selected_gem->GetIsSelected())
	{
		if (selected_gems.size() == 0)
		{
			selected_gems.push_back(selected_gem);
			selected_gem->SetIsSelected(true);
		}
		else
		{
			gem* last_selected_gem = selected_gems[selected_gems.size() - 1];
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
	else if (!is_mouse_down)
	{
		const bool can_be_collected = selected_gems.size() > 2;
		for (auto gem : selected_gems)
		{
			if (can_be_collected)
			{
				gem->OnCollected();
				collected_gems.push_back(gem);
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
			if (cell_to_spawn_in->GetCellState() == cell_states::empty && collected_gems.size() > 0)
			{
				gem* gem_to_spawn = collected_gems.back();
				collected_gems.pop_back();

				gem_to_spawn->SetGemType(static_cast<gem_types>(rand() % 5));
				gem_to_spawn->SetCurrentCell(cell_to_spawn_in);
				cell_to_spawn_in->SetCurrentGem(gem_to_spawn);
				auto t = gem_to_spawn->GetObjectTransform();
				t.translation = cell_to_spawn_in->translation;
				t.translation.y += BOARD_TILE_SPACE;
				gem_to_spawn->SetObjectTransform(t);
				gem_to_spawn->OnReturn();
			}
		}
	}
}

void game_board::CreateBoard()
{
	const auto vert_src =
		dreco::file_utils::LoadSourceFromFile("res/shaders/default_shader.vert");
	const auto frag_src =
		dreco::file_utils::LoadSourceFromFile("res/shaders/default_shader.frag");

	const dreco::shader_properties shader_prop =
		dreco::shader_properties(vert_src.c_str(), frag_src.c_str());

	dreco::vertex_properties vert_prop = dreco::vertex_properties::ModelPlane();

	LoadGemTextures();

	dreco::transform gem_trans = dreco::transform();
	gem_trans.scale = dreco::vec2(0.15f, 0.15f);

	const uint16_t TOTAL_GEMS = BOARD_WIDTH * BOARD_HEIGHT;

	for (uint8_t i = 0; i < TOTAL_GEMS; ++i)
	{
		const uint8_t x = i >= BOARD_WIDTH ? i - ((i / BOARD_WIDTH) * BOARD_WIDTH) : i;
		const uint8_t y = i >= BOARD_WIDTH ? i / BOARD_WIDTH : 0;
		cells[x][y] = new board_cell(*this, dreco::int_vec2(x, y));

		gem* cur_gem = new gem(vert_prop, shader_prop, *this);
		gems[i] = cur_gem;

		const std::string obj_name = "gem_" + std::to_string(i);
		GetWorld()->RegisterObject(obj_name, *cur_gem);
		gem_trans.translation =
			dreco::vec2(BOARD_TILE_SPACE * x - BOARD_CENTER_OFFSET_WIDTH,
				BOARD_TILE_SPACE * y - BOARD_CENTER_OFFSET_HEIGHT);

		cur_gem->SetObjectTransform(gem_trans);
		cur_gem->SetGemType(static_cast<gem_types>(rand() % 5));
		cur_gem->SetCurrentCell(cells[x][y]);
		cells[x][y]->SetCurrentGem(cur_gem);
	}
}

dreco::texture* game_board::GetGemTexture(const gem_types& _t) const
{
	return gem_textures.at(_t);
}

board_cell* game_board::GetCellFromPosition(const dreco::int_vec2& _p) const
{
	return cells[_p.x][_p.y];
}

void game_board::LoadGemTextures()
{
	gem_textures.emplace(gem_types::red, new dreco::texture("res/textures/gem_red.png"));
	gem_textures.emplace(
		gem_types::blue, new dreco::texture("res/textures/gem_blue.png"));
	gem_textures.emplace(
		gem_types::green, new dreco::texture("res/textures/gem_green.png"));
	gem_textures.emplace(
		gem_types::purple, new dreco::texture("res/textures/gem_purple.png"));
	gem_textures.emplace(
		gem_types::yellow, new dreco::texture("res/textures/gem_yellow.png"));
}
