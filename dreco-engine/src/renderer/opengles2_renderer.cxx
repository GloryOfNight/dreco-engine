#include "opengles2_renderer.hxx"

#include "../core/engine.hxx"
#include "gl_inline_functions.hxx"
#include "shader_utils.hxx"

using namespace dreco;

opengles2_renderer::opengles2_renderer(engine& _e)
{
	engine_owner = &_e;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);

	gl_context = SDL_GL_CreateContext(engine_owner->GetWindow());

	LoadGlFunctions();

	const auto vert_src = shader_utils::LoadShaderSource("res/shaders/vert_default.vert");
	const auto frag_src = shader_utils::LoadShaderSource("res/shaders/frag_default.frag");

	glShaderAtributes s_attr = {{0, "a_position"}, {1, "a_color"}, {2, "a_tex_coord"}};

	shader = new shader_gl_base(*vert_src.c_str(), *frag_src.c_str(), s_attr);
}

opengles2_renderer::~opengles2_renderer()
{
	delete shader;
	SDL_GL_DeleteContext(gl_context);
}
