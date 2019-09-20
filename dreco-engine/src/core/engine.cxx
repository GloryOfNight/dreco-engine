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
		delete renderer;
		delete event_manager;
		SDL_DestroyWindow(window);
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
	event_manager->AddEventBinding(SDL_QUIT, std::bind(&engine::Event_Quit, this));

	renderer = new opengles2_renderer(*this);
	
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

void engine::Event_Quit()
{
	StopMainLoop();
}

inline sdl_event_manager* engine::GetEventManager() const
{
	return event_manager;
}

void engine::RegisterOwnedGame(game_base* game)
{
	owned_game = game;
}

SDL_Window* engine::GetWindow() const
{
	return window;
}

opengles2_renderer* engine::GetRenderer() const 
{
	return renderer;
}

void engine::Tick(const float& DeltaTime)
{
	owned_game->Tick(DeltaTime);
	GetEventManager()->ProcessEvents();

	renderer->Tick(DeltaTime);
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