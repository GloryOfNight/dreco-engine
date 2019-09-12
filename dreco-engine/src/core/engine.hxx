#pragma once
#include "SDL2/SDL.h"
#include "engine_properties.hxx"
#include "sdl_event_manager.hxx"
#include "types.hxx"

namespace dreco
{
class engine
{
public:
	engine();
	~engine();
	int Init(engine_properties& properties);

	void StartMainLoop();

	void StopMainLoop();

	void Key_Escape(uint32_t event_type);

	inline sdl_event_manager* GetEventManager() const;

private:
	void Tick(const float& DeltaTime);

	float GetNewDeltaTime();

	sdl_event_manager* CreateEventManager();

	uint32_t last_tick_time = 0;

	bool is_engine_initialized = false;

	SDL_Window* window = nullptr;

	bool keep_main_loop = false;

	sdl_event_manager* event_manager = nullptr;
};
}	// namespace dreco