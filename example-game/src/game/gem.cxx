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