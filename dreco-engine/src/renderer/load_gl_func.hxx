#pragma once
#include "SDL2/SDL.h"

template <typename T>
static void load_gl_func(const char* func_name, T& result)
{
	void* gl_pointer = SDL_GL_GetProcAddress(func_name);
	if (nullptr == gl_pointer)
	{
		throw std::runtime_error(std::string("can't load GL function") + func_name);
	}
	result = reinterpret_cast<T>(gl_pointer);
}