#include "game_world.hxx"
#include "game_object.hxx"
#include "camera_base.hxx"

using namespace dreco;

game_world::game_world(game_base& _gi) : gi_owner(&_gi)
{
}

game_world::~game_world()
{
    delete[] &world_objects;
    delete player_camera;
}

void game_world::Init()
{
    CreatePlayerCamera();
}

void game_world::Tick(const float& DeltaTime)
{
    for (auto object : world_objects) 
    {
        object.second->Tick(DeltaTime);
    }
}

game_base* game_world::GetGameInstance() const
{
	return gi_owner;
}

game_object* game_world::GetObject(const std::string _obj_name) const
{
    return world_objects.at(_obj_name);
}

camera_base* game_world::GetPlayerCamera() const 
{
    return player_camera;
}

void game_world::CreatePlayerCamera()  
{
    player_camera = new camera_base();
    player_camera->Init(*this);
}

void game_world::RegisterObject(const std::string _obj_name, game_object& _obj) 
{
    world_objects.emplace(_obj_name, &_obj);

    _obj.Init(*this);
}