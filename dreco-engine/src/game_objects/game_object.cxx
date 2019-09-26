#include "game_object.hxx"

using namespace dreco;

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

void game_object::SetObjectTransform(transform& _t) 
{
    object_transform = _t;
}