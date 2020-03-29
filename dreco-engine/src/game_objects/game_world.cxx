#include "game_world.hxx"
#include "game_object.hxx"
#include "camera_base.hxx"

using namespace dreco;

game_world::game_world(game_base* _gi) : gi_owner(_gi)
{
    player_camera = new camera_base(this);
    RegisterObject("camera", *player_camera);
}

game_world::~game_world()
{
    for (auto obj : world_objects) 
    {
        delete obj.second;
    }
}

void game_world::Tick(const float& DeltaTime)
{
    for (auto object : world_objects) 
    {
        if (!object.second->GetIsBegined()) 
        {
            object.second->Begin();
        }

        object.second->Tick(DeltaTime);
    }
}

game_base* game_world::GetGameInstance() const
{
	return gi_owner;
}

game_object* game_world::GetObject(const char* _name) const
{
    return world_objects.at(_name);
}

camera_base* game_world::GetPlayerCamera() const 
{
    return player_camera;
}

const world_objects_map& game_world::GetWorldObjectsRef() const
{
    return world_objects;
} 

void game_world::RegisterObject(const char* _name, game_object& _obj) 
{
    world_objects.emplace(_name, &_obj);
}