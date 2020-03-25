#pragma once
#include "board_cell.hxx"
#include "board_constants.hxx"
#include "game_objects/game_object.hxx"
#include "gem_types.hxx"
#include "resources/texture.hxx"
#include "resources/audio.hxx"

#include <vector>

class gem;

class game_instance;

class game_board : public dreco::game_object
{
public:
	game_board();

	virtual ~game_board() override;

	virtual void Init(dreco::game_world& _w) override;

	virtual void Tick(const float& DeltaTime) override;

	void CreateBoard();

	dreco::texture* GetGemTexture(const gem_types& _t) const;

	board_cell* GetCellFromPosition(const dreco::int_vec2& _p) const;

private:	
	uint8_t reciently_removed_gems_count = 0;
	float reciently_removed_gems_timer = 0.1f;

	void LoadGemTextures();

	game_instance* gi;

	board_cell* cells[BOARD_WIDTH][BOARD_HEIGHT] = {};

	gem* gems[BOARD_WIDTH * BOARD_HEIGHT] = {};

	std::vector<gem*> selected_gems = {};

	std::vector<gem*> collected_gems = {};
};