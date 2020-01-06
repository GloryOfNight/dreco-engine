#include "core/engine.hxx"
#include "game_instance.hxx"

#ifdef __ANDROID__

#endif

#include <iostream>

#ifdef __ANDROID__
extern "C" int android_main();
#endif


int main()
{
	dreco::engine* engine = new dreco::engine();

	auto engine_properties = dreco::engine_properties();
	engine_properties.window_title = "Example Game";

	const auto init_res = engine->Init(engine_properties);

	if (init_res == dreco::INIT_SUCCESS)
	{
		dreco::game_base* game = new game_instance(*engine);
		game->Init();
		engine->RegisterOwnedGame(game);
		engine->StartMainLoop();
		// on main loop finished
		delete game;
	}

	delete engine;
	
	return 0;
}

#ifdef __ANDROID__
int android_main()
{
	return main();
}
#endif
