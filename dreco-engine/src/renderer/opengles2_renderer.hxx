#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#include "SDL2/SDL_opengl_glext.h"
#include "shader_gl_base.hxx"

namespace dreco
{
class engine;

class opengles2_renderer
{
public:
	opengles2_renderer(engine& _e);
	~opengles2_renderer();

private:
	engine* engine_owner = nullptr;

	SDL_GLContext gl_context = nullptr;

	shader_gl_base* shader = nullptr;
};
}	// namespace dreco