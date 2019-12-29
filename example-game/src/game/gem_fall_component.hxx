#pragma once
#include "board_constants.hxx"

class gem;

class board_cell;

class gem_fall_component
{
public:
    gem_fall_component(gem& _owner);

	void Tick(const float& DeltaTime);

    void TryFall(const bool _set_delay);

    void FallToCurrentCell();
private:
    void OnStartFall();

    void ProcessFall(const float& DeltaTime);

    gem& owner;

    bool is_in_fall = false;

    float delay_before_fall = GEM_DELAY_BEFORE_FALL;

    board_cell* previos_cell = nullptr;
    board_cell* next_cell = nullptr;
};