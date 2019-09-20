#pragma once
#include "game_objects/game_base.hxx"

class game_instance : public dreco::game_base
{
public:
	game_instance(dreco::engine& _e);

	void Tick(const float& DeltaTime) override;
};