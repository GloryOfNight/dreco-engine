#include "gem_fall_component.hxx"

#include "board_cell.hxx"
#include "game_board.hxx"
#include "gem.hxx"

gem_fall_component::gem_fall_component(gem& _owner) : owner(_owner)
{
}

void gem_fall_component::Tick(const float& DeltaTime)
{
	TryFall(/* set_delay */ true);

	if (is_in_fall)
	{
		if (delay_before_fall > 0.0f)
		{
			delay_before_fall -= DeltaTime;

			if (delay_before_fall <= 0.0f)
			{
				OnStartFall();
			}
		}
		else
		{
			ProcessFall(DeltaTime);
		}
	}
}

void gem_fall_component::TryFall(const bool _set_delay)
{
	if (!is_in_fall && owner.GetCell() && owner.GetCell()->GetPosition().y > 0)
	{
		game_board* board = owner.GetBoard();
		dreco::int_vec2 pos = owner.GetCell()->GetPosition();
		pos.y -= 1;
		board_cell* down_cell = board->GetCellFromPosition(pos);

		if (down_cell->GetCellState() == cell_states::empty)
		{
			previos_cell = owner.GetCell();
			next_cell = down_cell;
            next_cell->SetCellState(cell_states::recieving);
			is_in_fall = true;

			if (_set_delay)
			{
				delay_before_fall = GEM_DELAY_BEFORE_FALL;
			}
			else
			{
				OnStartFall();
			}
		}
	}
}

void gem_fall_component::FallToCurrentCell() 
{
    previos_cell = nullptr;
    next_cell = owner.GetCell();
    next_cell->SetCellState(cell_states::recieving);
    is_in_fall = true;
    delay_before_fall = GEM_DELAY_BEFORE_FALL;
}

void gem_fall_component::OnStartFall()
{
	if (previos_cell)
		previos_cell->SetCurrentGem(nullptr);
	owner.SetCurrentCell(next_cell);
	next_cell->SetCurrentGem(&owner);
	next_cell->SetCellState(cell_states::recieving);
}

void gem_fall_component::ProcessFall(const float& DeltaTime)
{
	auto t = owner.GetTransform();
	t.translation.y -= GEM_FALL_SPEED * DeltaTime;

	if (t.translation.y <= next_cell->translation.y)
	{
		t.translation = next_cell->translation;
		next_cell->SetCellState(cell_states::stationary);
		is_in_fall = false;
		TryFall(/* set_delay */ false);
	}
	owner.SetTransform(t);
}
