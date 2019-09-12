#include "engine.hxx"

#include <functional>
#include <iostream>
#include <stdexcept>

// its ok to use global namespace in cxx
using namespace dreco;

engine::engine()
{
	last_tick_time = SDL_GetPerformanceCounter();
}

engine::~engine()
{
	if (is_engine_initialized)
	{
		SDL_DestroyWindow(window);
		delete event_manager;
	}
}

int engine::Init(engine_properties& properties)
{
	const int sdl_init_result = SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);

	if (sdl_init_result != INIT_SUCCESS)
	{
		std::cerr << "Init(): Unable to initialize SDL: " << SDL_GetError() << std::endl;
		return INIT_FAILED;
	}

	window = SDL_CreateWindow(properties.window_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 640,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	if (!window)
	{
		std::cerr << "Init(): Unadble to create window: " << SDL_GetError() << std::endl;
		return INIT_FAILED;
	}

	event_manager = CreateEventManager();

	event_manager->AddKeyBinding(SDLK_ESCAPE, std::bind(&engine::Key_Escape, this, 1));

	is_engine_initialized = true;
	return INIT_SUCCESS;
}

void engine::StartMainLoop()
{
	if (!is_engine_initialized)
	{
		std::cerr << "StartMainLoop(): Egnine must be initialized!" << std::endl;
		return;
	}

	keep_main_loop = true;

	while (keep_main_loop)
	{
		const auto DeltaTime = GetNewDeltaTime();
		Tick(DeltaTime);
	}
}

void engine::StopMainLoop()
{
	keep_main_loop = false;
}

void engine::Key_Escape(uint32_t event_type)
{
	StopMainLoop();
}

inline sdl_event_manager* engine::GetEventManager() const
{
	return event_manager;
}

void engine::Tick(const float& DeltaTime)
{
	GetEventManager()->ProcessEvents();
}

float engine::GetNewDeltaTime()
{
	const uint32_t now = SDL_GetPerformanceCounter();

	const float deltatime = static_cast<float>(now - last_tick_time) / static_cast<float>(SDL_GetPerformanceFrequency());

	last_tick_time = now;

	return deltatime;
}

sdl_event_manager* engine::CreateEventManager()
{
	return new sdl_event_manager;
}