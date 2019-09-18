#include "../../dreco-engine/src/core/engine.hxx"
#include "../../dreco-engine/src/game_objects/game_base.hxx"
#include <iostream>

int main()
{
	dreco::engine* engine = new dreco::engine();

	auto engine_properties = dreco::engine_properties();
	engine_properties.window_title = "Example Game";

	const auto init_res = engine->Init(engine_properties);

	if (init_res == dreco::INIT_SUCCESS)
	{
		dreco::game_base* game = new dreco::game_base(*engine);
		game->Init();
		engine->RegisterOwnedGame(game);
		engine->StartMainLoop();
		// on main loop finished
		delete game;
	}

	delete engine;

	return 0;
}