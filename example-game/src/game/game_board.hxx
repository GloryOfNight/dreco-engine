#pragma once
#include "board_cell.hxx"
#include "game_objects/game_object.hxx"
#include "gem_types.hxx"
#include "renderer/texture.hxx"

#include <map>

constexpr uint8_t BOARD_WIDTH = 7;
constexpr uint8_t BOARD_HEIGHT = 10;
constexpr float BOARD_TILE_SPACE = 0.15f;
constexpr float BOARD_CENTER_OFFSET_WIDTH =
	BOARD_WIDTH % 2 == 0 ? (BOARD_WIDTH * BOARD_TILE_SPACE) / 2
						 : (BOARD_WIDTH * BOARD_TILE_SPACE) / 2 - (BOARD_TILE_SPACE / 2);
constexpr float BOARD_CENTER_OFFSET_HEIGHT =
	BOARD_WIDTH % 2 == 0 ? (BOARD_HEIGHT * BOARD_TILE_SPACE) / 2
						 : (BOARD_HEIGHT * BOARD_TILE_SPACE) / 2 - (BOARD_TILE_SPACE / 2);

class gem;

class game_board : public dreco::game_object
{
public:
	game_board();

	virtual ~game_board() override;

	virtual void Init(dreco::game_world& _w) override;

	void CreateBoard();

	dreco::texture* GetGemTexture(const gem_types& _t) const;

private:
	void LoadGemTextures();

	board_cell* cells[BOARD_WIDTH * BOARD_HEIGHT] = {};

	gem* gems[BOARD_WIDTH * BOARD_HEIGHT] = {};

	// temporal solution for handling gem textures
	std::map<gem_types, dreco::texture*> gem_textures;
};