#include "opengles2_renderer.hxx"

#include "../core/engine.hxx"
#include "gl_inline_functions.hxx"
#include "utils/file_utils.hxx"

using namespace dreco;

opengles2_renderer::opengles2_renderer(engine& _e)
{
	engine_owner = &_e;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);

	gl_context = SDL_GL_CreateContext(engine_owner->GetWindow());

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

void opengles2_renderer::SwapBuffer()
{
	SDL_GL_SwapWindow(engine_owner->GetWindow());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}