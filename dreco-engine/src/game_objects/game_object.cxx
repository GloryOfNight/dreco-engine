#include "game_object.hxx"

using namespace dreco;

game_object::game_object(game_world* _w)
	: object_transform(transform()), IsBegined{false}, world(_w)
{
}

game_object::~game_object()
{
}

void game_object::Begin()
{
    IsBegined = true;
}

void game_object::Tick(const float& DeltaTime)
{
}

transform game_object::GetTransform() const
{
	return object_transform;
}

void game_object::SetTransform(const transform& _t)
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

resource_manager* game_object::GetResourceManager() const 
{
	return GetGameInstance()->GetResourceManager();
}

bool game_object::GetIsBegined() const 
{
    return IsBegined;
}