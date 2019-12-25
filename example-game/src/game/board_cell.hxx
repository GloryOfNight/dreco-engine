#pragma once
#include "cell_states.hxx"
#include "math/uint8_vec2.hxx"

class game_board;

class gem;

class board_cell
{
public:
	board_cell(game_board& _b, const dreco::uint8_vec2 _pos);

	dreco::uint8_vec2 GetPosition() const;

	gem* GetCurrentGem();

	void SetCurrentGem(gem* _g);

	cell_states GetCellState() const;

	void SetCellState(const cell_states _s);

private:
	dreco::uint8_vec2 position;

	game_board* board;

	gem* current_gem = nullptr;

	cell_states state = cell_states::stationary;
};