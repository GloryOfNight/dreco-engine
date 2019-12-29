#pragma once
#include "board_cell.hxx"
#include "game_objects/mesh_object.hxx"
#include "gem_types.hxx"

class game_board;

class gem_fall_component;

class gem : public dreco::mesh_object
{
public:
	gem(const dreco::vertex_properties& _v, const dreco::shader_properties& _shader_prop,
		game_board& _b);
	
	~gem();

	virtual void Tick(const float& DeltaTime) override;

	void SetGemType(gem_types _t);

	gem_types GetGemType() const;

	void SetCurrentCell(board_cell* _c);

	board_cell* GetCell() const;

	void SetIsSelected(const bool _v);

	bool GetIsSelected() const;

	game_board* GetBoard() const;
	
	void OnCollected();

	void OnReturn();
private:
	bool selected = false;

	gem_types type = gem_types::red;

	game_board& board;

	gem_fall_component& fall_component;

	board_cell* current_cell = nullptr;
};