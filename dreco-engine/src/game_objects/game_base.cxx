#include "game_base.hxx"
#include "../core/engine.hxx"

using namespace dreco;

game_base::game_base(engine& engine_based_on) 
{
    game_engine = &engine_based_on;
}

void game_base::Init() 
{
    
} 

void game_base::Tick(const float& DeltaTime)
{
    
}

engine* game_base::GetEngine() const 
{
    return game_engine;
}