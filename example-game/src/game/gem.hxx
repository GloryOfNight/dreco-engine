#pragma once
#include "board_cell.hxx"
#include "game_objects/mesh_object.hxx"
#include "gem_types.hxx"

class game_board;

class gem : public dreco::mesh_object
{
public:
	gem(const dreco::vertex_properties& _v, const dreco::shader_properties& _shader_prop,
		game_board& _b);
	
	void SetGemType(gem_types _t);

	gem_types GetGemType() const;

	void SetCurrentCell(board_cell* _c);

	board_cell* GetCell() const;

	void SetIsSelected(const bool _v);

	bool GetIsSelected() const;
private:
	bool selected = false;

	gem_types type = gem_types::red;

	game_board& board;

	board_cell* current_cell = nullptr;
};