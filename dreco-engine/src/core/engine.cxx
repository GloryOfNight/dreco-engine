#include "engine.hxx"

#include <functional>
#include <iostream>
#include <stdexcept>

#include "game_objects/game_world.hxx"
#include "game_objects/camera_base.hxx"

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
		SDL_Quit();
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
		std::cerr << "Init(): Unadle to create window: " << SDL_GetError() << std::endl;
		return INIT_FAILED;
	}

	event_manager = CreateEventManager();

	event_manager->AddKeyBinding(SDLK_ESCAPE, std::bind(&engine::Key_Escape, this, std::placeholders::_1));
	event_manager->AddEventBinding(SDL_QUIT, std::bind(&engine::Event_Quit, this, std::placeholders::_1));
	event_manager->AddEventBinding(SDL_WINDOWEVENT, std::bind(&engine::Event_Window, this, std::placeholders::_1));

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

vec2 engine::MouseCoordToWorld() 
{
	int x;
	int y;
	SDL_GetMouseState(&x, &y);

	const vec2 wincoor = vec2(static_cast<float>(x), static_cast<float>(y));

	int w = 0;
	int h = 0;
	SDL_GetWindowSize(this->GetWindow(), &w, &h);
	const vec2 viewport = vec2(static_cast<float>(w), static_cast<float>(h));
	auto pm = owned_game->GetCurrentWorld()->GetPlayerCamera()->GetProjectionMatrix();
	mat2x3 pm2x3 = mat2x3::identiry();
	pm2x3.mat[0][0] = pm.mat[0][0];
	pm2x3.mat[0][1] = pm.mat[0][1];
	pm2x3.mat[0][2] = pm.mat[0][2];
	pm2x3.mat[1][0] = pm.mat[1][0];
	pm2x3.mat[1][1] = pm.mat[1][1];
	pm2x3.mat[1][2] = pm.mat[1][2];

	return renderer->UnProject(wincoor, viewport,
	 owned_game->GetCurrentWorld()->GetPlayerCamera()->GetViewMatrix(),
	  pm2x3);
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