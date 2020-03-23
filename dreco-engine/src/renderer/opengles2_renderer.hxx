#pragma once

#ifdef __ANDROID__
#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_opengl_glext.h"
#else
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#include "SDL2/SDL_opengl_glext.h"
#endif

#include "shader_gl_base.hxx"
#include "vertex.hxx"

#include <vector>
#include <string>

namespace dreco
{
class engine;

class opengles2_renderer
{
public:
	opengles2_renderer(engine& _e);
	~opengles2_renderer();

	int Init(const std::string& _window_title);

	void DrawVertexArray(const std::vector<vertex>& _v, const mat2x3& _m);

	void Tick(const float& DeltaTime);

	void UpdateViewportSize();

	int GetColorIndexFromPixel(const vec2& _p_coord);

	void DrawScene();

	SDL_Window* GetWindow() const;
private:
	void SwapBuffer();

	void ClearBuffers();
	
	engine* engine_owner = nullptr;

	SDL_GLContext gl_context = nullptr;

	SDL_Window* window = nullptr;
};
}	// namespace dreco