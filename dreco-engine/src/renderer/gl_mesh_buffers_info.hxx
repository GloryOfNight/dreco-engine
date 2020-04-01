#pragma once

#ifdef __ANDROID__
#include "SDL_opengl.h"
#else
#include "SDL2/SDL_opengl.h"
#endif

namespace dreco
{
struct gl_mesh_buffers_info
{
	gl_mesh_buffers_info()
	{
	}

	gl_mesh_buffers_info(
		const GLuint& _vbo_vert, const GLuint& _ibo_element, const GLuint& _vbo_tc)
		: vbo_vertex{_vbo_vert}, ibo_element{_ibo_element}, vbo_tc{_vbo_tc}
	{
	}

	GLuint vbo_vertex;
	GLuint ibo_element;
	GLuint vbo_tc;
};
}	 // namespace dreco