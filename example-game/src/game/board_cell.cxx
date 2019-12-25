#include "board_cell.hxx"

board_cell::board_cell(game_board& _b, const dreco::uint8_vec2 _pos) : board(&_b), position(_pos)
{
}

dreco::uint8_vec2 board_cell::GetPosition() const 
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