#include "gem.hxx"
#include "game_board.hxx"

gem::gem(const dreco::vertex_properties& _v, const dreco::shader_properties& _shader_prop, game_board& _b)
	: dreco::mesh_object(_v, _shader_prop), board(_b)
{
}

void gem::SetGemType(gem_types _t) 
{
	type = _t;
	SetTexture(*board.GetGemTexture(type));
}

gem_types gem::GetGemType() const 
{
	return type;
}

void gem::SetCurrentCell(board_cell* _c) 
{
	current_cell = _c;
	current_cell->SetCurrentGem(this);
}

board_cell* gem::GetCell() const
{
	return current_cell;
}

void gem::SetIsSelected(const bool _v) 
{
	selected = _v;

	auto t = GetObjectTransform();
	t.scale += _v ? 0.03 : -0.03;
	SetObjectTransform(t);
}

bool gem::GetIsSelected() const 
{
	return selected;
}