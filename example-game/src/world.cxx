#include "world.hxx"

#include "game/game_board.hxx"
#include "game_objects/camera_base.hxx"
#include "game_objects/game_object.hxx"
#include "utils/file_utils.hxx"

#include <memory>

void world::Init()
{
	game_world::Init();

	dreco::game_object* obj = new game_board();
	RegisterObject("game_board", *obj);
}

void world::Tick(const float& DeltaTime)
{
	game_world::Tick(DeltaTime);

	/*
	 auto t = GetPlayerCamera()->GetObjectTransform();

		t.translation.y -= 0.1 *DeltaTime;
		t.translation.x -= 0.1 *DeltaTime;

	 GetPlayerCamera()->SetObjectTransform(t); 
	 */
}