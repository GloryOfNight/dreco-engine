#pragma once
#include "SDL2/SDL.h"
#include "engine_properties.hxx"
#include "game_objects/game_base.hxx"
#include "renderer/opengles2_renderer.hxx"
#include "sdl_event_manager.hxx"
#include "types.hxx"

#include <stdint.h>

namespace dreco
{
class engine
{
public:
	engine();
	~engine();
	int Init(engine_properties& _p);

	void StartMainLoop();

	void StopMainLoop();

	void Key_Escape(uint32_t event_type);

	void Event_Quit(const SDL_Event& _e);

	void Event_Window(const SDL_Event& _e);

	sdl_event_manager* GetEventManager() const;

	void RegisterOwnedGame(game_base* game);

	SDL_Window* GetWindow() const;

	opengles2_renderer* GetRenderer() const;

	game_base* GetOwnedGame() const;

private:
	void Tick(const float& DeltaTime);

	float GetNewDeltaTime();

	sdl_event_manager* CreateEventManager();

	uint32_t last_tick_time = 0;

	bool is_engine_initialized = false;

	bool keep_main_loop = false;

	sdl_event_manager* event_manager = nullptr;

	game_base* owned_game = nullptr;

	opengles2_renderer* renderer = nullptr;
};
}	 // namespace dreco