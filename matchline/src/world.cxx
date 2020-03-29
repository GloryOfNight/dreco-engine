#include "world.hxx"

#include "game/game_board.hxx"
#include "game_instance.hxx"
#include "game_objects/camera_base.hxx"
#include "game_objects/game_object.hxx"
#include "utils/file_utils.hxx"

#include <memory>

world::world(game_instance* gi) : game_world(gi)
{
	dreco::game_object* obj = new game_board(this);
	RegisterObject("game_board", *obj);
}

void world::Tick(const float& DeltaTime)
{
	game_world::Tick(DeltaTime);
}