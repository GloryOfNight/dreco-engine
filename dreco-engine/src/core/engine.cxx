#include "engine.hxx"

#include "game_objects/camera_base.hxx"
#include "game_objects/game_world.hxx"

#include <functional>
#include <iostream>
#include <stdexcept>

// its ok to use global namespace in cxx
using namespace dreco;

engine::engine() : last_tick_time{SDL_GetPerformanceCounter()}
{
}

engine::~engine()
{
	if (is_engine_initialized)
	{
		delete renderer;
		delete event_manager;
		delete resource_manager_;
		delete audio_manager_;
		SDL_Quit();
	}
}

int engine::Init(const engine_properties& _p)
{
	const int sdl_init_result = SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);

	if (sdl_init_result == INIT_FAILED)
	{
		std::cerr << "Init(): Unable to initialize SDL: " << SDL_GetError() << std::endl;
		delete this;
		std::runtime_error("Failed to initialize SDL");
		return INIT_FAILED;
	}

	renderer = new opengles2_renderer(*this);
	const int renderer_init_res = renderer->Init(_p.window_title);

	if (renderer_init_res == INIT_FAILED)
	{
		std::cerr << "Init(): Renderer initialize failed: " << SDL_GetError()
				  << std::endl;
		delete this;
		std::runtime_error("Failed to initialize renderer");
		return INIT_FAILED;
	}

	event_manager = CreateEventManager();

	event_manager->AddKeyBinding(
		SDLK_ESCAPE, std::bind(&engine::Key_Escape, this, std::placeholders::_1));
	event_manager->AddEventBinding(
		SDL_QUIT, std::bind(&engine::Event_Quit, this, std::placeholders::_1));
	event_manager->AddEventBinding(
		SDL_WINDOWEVENT, std::bind(&engine::Event_Window, this, std::placeholders::_1));

	resource_manager_ = CreateResourceManager();

	audio_manager_ = CreateAudioManager();

	is_engine_initialized = true;

	return INIT_SUCCESS;
}

void engine::StartMainLoop()
{
	if (is_engine_initialized)
	{
		keep_main_loop = true;

		while (keep_main_loop)
		{
			const float DeltaTime{GetNewDeltaTime()};
			Tick(DeltaTime);
		}
	}
	else
	{
		std::cerr << "StartMainLoop(): Egnine must be initialized!" << std::endl;
		return;
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

void engine::Event_Quit(const SDL_Event& _e)
{
	StopMainLoop();
}

void engine::Event_Window(const SDL_Event& _e)
{
	if (_e.window.event == SDL_WINDOWEVENT_RESIZED)
	{
		renderer->UpdateViewportSize();
		owned_game->OnWindowResize();
	}
}

sdl_event_manager* engine::GetEventManager() const
{
	return event_manager;
}

void engine::RegisterOwnedGame(game_base* game)
{
	owned_game = game;
}

SDL_Window* engine::GetWindow() const
{
	return renderer->GetWindow();
}

opengles2_renderer* engine::GetRenderer() const
{
	return renderer;
}

game_base* engine::GetOwnedGame() const
{
	return owned_game;
}

resource_manager* engine::GetResourceManager() const
{
	return resource_manager_;
}

audio_manager* engine::GetAudioManager() const
{
	return audio_manager_;
}

void engine::Tick(const float& DeltaTime)
{
	GetEventManager()->ProcessEvents();
	owned_game->Tick(DeltaTime);
	renderer->Tick(DeltaTime);
}

float engine::GetNewDeltaTime()
{
	const uint64_t now{SDL_GetPerformanceCounter()};

	const float deltatime =
		static_cast<float>(now - last_tick_time) / static_cast<float>(SDL_GetPerformanceFrequency());

	last_tick_time = now;

	return deltatime;
}

sdl_event_manager* engine::CreateEventManager()
{
	return new sdl_event_manager;
}

resource_manager* engine::CreateResourceManager()
{
	return new resource_manager(*this);
}

audio_manager* engine::CreateAudioManager()
{
	return new audio_manager(*this);
}