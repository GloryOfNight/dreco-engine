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

#include "gl_mesh_buffers_info.hxx"
#include "mesh_data.hxx"
#include "gl_shader_base.hxx"

#include <string>
#include <map>
#include <vector>

namespace dreco
{
class engine;

class opengles2_renderer
{
public:
	opengles2_renderer(engine& _e);
	~opengles2_renderer();

	int Init(const char* _title);

	void Tick(const float& DeltaTime);

	void UpdateViewportSize();

	int GetColorIndexFromPixel(const vec2& _p_coord);

	void DrawScene();

	SDL_Window* GetWindow() const;

	void AddMeshData(mesh_data* _mesh_data);

	gl_mesh_buffers_info GetMeshDataBufferInfo(const mesh_data* _mesh_data) const;

private:
	void SwapBuffer();

	void ClearBuffers();

	std::map<mesh_data*, gl_mesh_buffers_info> meshes_buffers_info{};

	engine* engine_owner = nullptr;

	SDL_GLContext gl_context = nullptr;

	SDL_Window* window = nullptr;
};
}	 // namespace dreco