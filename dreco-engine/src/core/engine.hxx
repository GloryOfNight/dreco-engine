#pragma once

#ifdef __ANDROID__
#include "SDL.h"
#else
#include "SDL2/SDL.h"
#endif

#include "audio_manager.hxx"
#include "engine_properties.hxx"
#include "game_objects/game_base.hxx"
#include "renderer/opengles2_renderer.hxx"
#include "resource_manager.hxx"
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
	int Init(const engine_properties& _p);

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

	resource_manager* GetResourceManager() const;

	audio_manager* GetAudioManager() const;

private:
	void Tick(const float& DeltaTime);

	inline float GetNewDeltaTime();

	inline sdl_event_manager* CreateEventManager();

	inline resource_manager* CreateResourceManager();

	inline audio_manager* CreateAudioManager();

	uint64_t last_tick_time = 0;

	bool is_engine_initialized = false;

	bool keep_main_loop = false;

	game_base* owned_game = nullptr;

	opengles2_renderer* renderer = nullptr;

	sdl_event_manager* event_manager = nullptr;

	resource_manager* resource_manager_ = nullptr;

	audio_manager* audio_manager_ = nullptr;
};
}	 // namespace dreco