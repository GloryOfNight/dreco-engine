#pragma once
#include "game_base.hxx"

#include <map>

namespace dreco
{
class game_object;
class camera_base;

class game_world
{
public:
	game_world(game_base& _gi);
	~game_world();

	virtual void Init();

	virtual void Tick(const float& DeltaTime);

	game_base* GetGameInstance() const;

	game_object* GetObject(const std::string _obj_name) const;

	camera_base* GetPlayerCamera() const;

protected:
	virtual void CreatePlayerCamera();

	void RegisterObject(const std::string _obj_name, game_object& _obj);

private:
	camera_base* player_camera = nullptr;

	game_base* gi_owner = nullptr;

	std::map<std::string, game_object*> world_objects = {};
};
}	// namespace dreco