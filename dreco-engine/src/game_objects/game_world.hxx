#pragma once
#include "game_base.hxx"

#include <map>
#include <string>

namespace dreco
{
class game_object;
class camera_base;

typedef std::map<std::string, game_object*> world_objects_map;

class game_world
{
public:
	game_world(game_base& _gi);
	virtual ~game_world();

	virtual void Init();

	virtual void Tick(const float& DeltaTime);

	game_base* GetGameInstance() const;

	game_object* GetObject(const char* _name) const;

	camera_base* GetPlayerCamera() const;

	const world_objects_map& GetWorldObjectsRef() const;

	void RegisterObject(const char* _name, game_object& _obj);

protected:
	virtual void CreatePlayerCamera();

private:
	camera_base* player_camera = nullptr;

	game_base* gi_owner = nullptr;

	world_objects_map world_objects = {};
};
}	 // namespace dreco