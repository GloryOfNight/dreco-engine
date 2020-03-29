#pragma once
#include "game_objects/game_world.hxx"

class game_instance;

class world : public dreco::game_world 
{
    public:
    world(game_instance* gi);

    virtual void Tick(const float& DeltaTime) override;
};