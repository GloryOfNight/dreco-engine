#include "opengles2_renderer.hxx"

#include <glm/gtc/matrix_transform.hpp>
#include "../core/engine.hxx"
#include "gl_inline_functions.hxx"
#include "math/vec3.hxx"
#include "utils/file_utils.hxx"

using namespace dreco;

opengles2_renderer::opengles2_renderer(engine& _e)
{
	engine_owner = &_e;
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);

	gl_context = SDL_GL_CreateContext(engine_owner->GetWindow());

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	LoadGlFunctions();
}

opengles2_renderer::~opengles2_renderer()
{
	SDL_GL_DeleteContext(gl_context);
}

void opengles2_renderer::Tick(const float& DeltaTime)
{
	SwapBuffer();
}

void opengles2_renderer::UpdateViewportSize()
{
	int w = 0;
	int h = 0;
	SDL_GetWindowSize(engine_owner->GetWindow(), &w, &h);

	glViewport(0, 0, w, h);
}

vec2 opengles2_renderer::UnProject(const vec2& _wincoord, const vec2& _viewport, const mat2x3& _m, const mat2x3& _p) 
{
	mat2x3 pm = _p * _m;
	pm = mat2x3::inverse(pm);

	vec3 in;
	in.x = 	((_wincoord.x / _viewport.x) * 2) - 1.0f;
	in.y = 1.0f - ((_wincoord.y / _viewport.y) * 2);
	in.z = 1;

	vec3 pos = in * pm;

	return vec2(pos.x, pos.y);
}

void opengles2_renderer::SwapBuffer()
{
	SDL_GL_SwapWindow(engine_owner->GetWindow());
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}