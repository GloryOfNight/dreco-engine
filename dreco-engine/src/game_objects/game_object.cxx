#include "game_object.hxx"

using namespace dreco;

void game_object::Init()
{
}

void game_object::Tick(const float& DeltaTime)
{
}

transform game_object::GetObjectTransform() 
{
    return object_transform;
}

void game_object::SetObjectTransform(transform& _t) 
{
    object_transform = _t;
}