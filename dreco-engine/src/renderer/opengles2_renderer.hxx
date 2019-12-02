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

	uint8_t GetStencilIndexFromPixel(const vec2& _p_coord);

	void DrawScene();

private:
	void SwapBuffer();

	void ClearBuffers();
	
	engine* engine_owner = nullptr;

	SDL_GLContext gl_context = nullptr;
};
}	// namespace dreco