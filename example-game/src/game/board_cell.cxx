#include "board_cell.hxx"

#include "board_constants.hxx"

board_cell::board_cell(game_board& _b, const dreco::int_vec2 _pos)
	: board(&_b)
	, position(_pos)
	, translation(dreco::vec2(BOARD_TILE_SPACE * _pos.x - BOARD_CENTER_OFFSET_WIDTH,
		  BOARD_TILE_SPACE * _pos.y - BOARD_CENTER_OFFSET_HEIGHT))
{
}

dreco::int_vec2 board_cell::GetPosition() const
{
	return position;
}

gem* board_cell::GetCurrentGem()
{
	return current_gem;
}

void board_cell::SetCurrentGem(gem* _g)
{
	current_gem = _g;

	if (_g == nullptr)
	{
		SetCellState(cell_states::empty);
	}
}

cell_states board_cell::GetCellState() const
{
	return state;
}

void board_cell::SetCellState(const cell_states _s)
{
	state = _s;
}