#include "gem.hxx"

#include "game_board.hxx"
#include "gem_fall_component.hxx"
#include "core/resource_manager.hxx"
#include "core/audio_manager.hxx"


gem::gem(dreco::game_world* _w, const dreco::mesh_data* _mesh_data, const dreco::shader_properties& _s,
	game_board& _b)
	: dreco::mesh_object(_w, _mesh_data, _s)
	, board(&_b)
	, fall_component(new gem_fall_component(*this))
{
}

gem::~gem()
{
	delete fall_component;
}

void gem::Tick(const float& DeltaTime)
{
	fall_component->Tick(DeltaTime);
}

void gem::SetGemType(gem_types _t)
{
	type = _t;
	SetTexture(board->GetGemTexture(type));
}

gem_types gem::GetGemType() const
{
	return type;
}

void gem::SetCurrentCell(board_cell* _c)
{
	if (current_cell)
	{
		current_cell->SetCurrentGem(_c == nullptr ? nullptr : this);
	}

	current_cell = _c;
}

board_cell* gem::GetCell() const
{
	return current_cell;
}

void gem::SetIsSelected(const bool _v)
{
	selected = _v;

	auto t = GetTransform();
	t.scale += _v ? 0.03 : -0.03;
	SetTransform(t);
}

bool gem::GetIsSelected() const
{
	return selected;
}

game_board* gem::GetBoard() const
{
	return board;
}

void gem::OnCollected()
{
	SetCurrentCell(nullptr);
	SetIsSelected(false);
	SetIsRendered(false);
}

void gem::OnReturn()
{
	SetIsRendered(true);
	fall_component->FallToCurrentCell();
}