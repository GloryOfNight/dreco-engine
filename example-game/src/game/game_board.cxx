#include "game_board.hxx"

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
}

void game_board::Init(dreco::game_world& _w)
{
	game_object::Init(_w);
	CreateBoard();
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
	uint16_t gem_counter = 0;

	for (uint8_t w = 0; w < BOARD_WIDTH; ++w)
	{
		for (uint8_t h = 0; h < BOARD_HEIGHT; ++h)
		{
			gem* cur_gem = gems[w][h];
			cur_gem = new gem(vert_prop, shader_prop, *this);
			++gem_counter;

			const std::string obj_name = "gem_" + std::to_string(gem_counter);
			GetWorld()->RegisterObject(obj_name, *cur_gem);
			gem_trans.translation =
				dreco::vec2(BOARD_TILE_SPACE * w - BOARD_CENTER_OFFSET_WIDTH,
					BOARD_TILE_SPACE * h - BOARD_CENTER_OFFSET_HEIGHT);
			cur_gem->SetObjectTransform(gem_trans); 
			cur_gem->SetGemType(static_cast<gem_types>(rand() % 5));
		}
	}
}

dreco::texture* game_board::GetGemTexture(const gem_types& _t) const
{
	return gem_textures.at(_t);
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