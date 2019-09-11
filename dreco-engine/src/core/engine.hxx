#pragma once
#include "SDL2/SDL.h"
#include "engine_properties.hxx"
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

private:

	float GetNewDeltaTime();

	uint32_t last_tick_time = 0;
	
	bool is_engine_initialized = false;

	SDL_Window* window = nullptr;

	bool keep_main_loop = false;
};
}	// namespace dreco