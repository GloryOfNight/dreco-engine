#include "game_object.hxx"

using namespace dreco;

game_object::game_object() 
{
}

game_object::~game_object() 
{
}

void game_object::Init(game_world& _w)
{
    world = &_w;
}

void game_object::Tick(const float& DeltaTime)
{
}

transform game_object::GetObjectTransform() const
{
    return object_transform;
}

void game_object::SetObjectTransform(const transform& _t) 
{
    object_transform = _t;
}

game_world* game_object::GetWorld() const
{
    return world;
}

game_base* game_object::GetGameInstance() const
{
    return world->GetGameInstance();
}