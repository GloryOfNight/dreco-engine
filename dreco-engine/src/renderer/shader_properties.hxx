#pragma once
#include "SDL2/SDL_opengl.h"

#include <tuple>
#include <vector>

namespace dreco
{
struct shader_properties
{
	shader_properties(const char* _vert_src, const char* _frag_src)
		: vert_src(_vert_src), frag_src(_frag_src)
	{
	}

	const char* vert_src = nullptr;
	const char* frag_src = nullptr;
};
}	// namespace dreco