#include "engine.hxx"

#include <iostream>
#include <stdexcept>

// its ok to use global namespace in cxx
using namespace dreco;

engine::engine()
{
}

engine::~engine()
{
	if (is_engine_initialized) 
	{
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

	is_engine_initialized= true;
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

	while(keep_main_loop) 
	{
		SDL_Event event;
		
		while(SDL_PollEvent(&event)) 
		{
			switch(event.type) 
			{
				case SDLK_DOWN:
				switch(event.key.keysym.sym) 
				{
					case SDLK_ESCAPE:
					StopMainLoop();
					break;
					
				}
				break;

				case SDL_QUIT:
				StopMainLoop();
				break;
			}
		}
	}
}

void engine::StopMainLoop() 
{
	keep_main_loop = false;
}