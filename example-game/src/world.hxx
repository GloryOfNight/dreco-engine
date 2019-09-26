#pragma once
#include "game_objects/game_world.hxx"

class world : public dreco::game_world 
{
    public:
    using game_world::game_world;

    virtual void Init() override;

};