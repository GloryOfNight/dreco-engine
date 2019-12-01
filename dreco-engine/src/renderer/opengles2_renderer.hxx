#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#include "SDL2/SDL_opengl_glext.h"
#include "shader_gl_base.hxx"
#include "vertex.hxx"

#include <vector>

namespace dreco
{
class engine;

class opengles2_renderer
{
public:
	opengles2_renderer(engine& _e);
	~opengles2_renderer();

	void DrawVertexArray(const std::vector<vertex>& _v, const mat2x3& _m);

	void Tick(const float& DeltaTime);

	void UpdateViewportSize();

	static vec2 UnProject(const vec2& _wincoord, const vec2& _viewport, 
			const mat2x3& _m, const mat2x3& _p);

	void DrawScene();
private:
	void SwapBuffer();

	engine* engine_owner = nullptr;

	SDL_GLContext gl_context = nullptr;
};
}	// namespace dreco