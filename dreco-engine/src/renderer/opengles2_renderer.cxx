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

	const auto vert_src = shader_utils::LoadShaderSource("res/shaders/default_shader.vert");
	const auto frag_src = shader_utils::LoadShaderSource("res/shaders/default_shader.frag");

	glShaderAtributes s_attr = {{0, "a_position"}, {1, "a_color"}, {2, "a_tex_coord"}};

	shader = new shader_gl_base(*vert_src.c_str(), *frag_src.c_str(), s_attr);
}

opengles2_renderer::~opengles2_renderer()
{
	delete shader;
	SDL_GL_DeleteContext(gl_context);
}

void opengles2_renderer::DrawVertexArray(const std::vector<vertex>& _v) 
{
	shader->Use();
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), &_v[0]);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, _v.capacity());
}

void opengles2_renderer::Tick(const float& DeltaTime) 
{
	SwapBuffer();
}

void opengles2_renderer::SwapBuffer() 
{
	SDL_GL_SwapWindow(engine_owner->GetWindow());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}