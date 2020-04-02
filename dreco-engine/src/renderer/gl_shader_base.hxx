#pragma once

#ifdef __ANDROID__
#include "SDL_opengl.h"
#else
#include "SDL2/SDL_opengl.h"
#endif

#include "math/mat2x3.hxx"
#include "gl_shader_info.hxx"
#include "core/resource_manager.hxx"

#include <string_view>
#include <tuple>
#include <vector>

namespace dreco
{
class gl_shader_base
{
public:
	gl_shader_base(const gl_shader_info& _info, resource_manager* _rm);
	~gl_shader_base();

	void Use();

	void SetUniform(const char* uniform_name, const mat2x3& _m);

	int GetUniformLocation(const char* uniform_name) const;

	int GetAttribLocation(const char* uniform_name) const;

private:
	GLuint CompileShader(GLenum _s_type, const char* _src, const size_t* _size);
	GLuint LinkShaderProgram();

	resource_manager* res_manager = nullptr;

	GLuint vert_shader_id = 0;
	GLuint frag_shader_id = 0;
	GLuint program_id = 0;
};
}	 // namespace dreco