#pragma once

#ifdef __ANDROID__
#include "SDL_opengl.h"
#else
#include "SDL2/SDL_opengl.h"
#endif

#include "math/mat2x3.hxx"
#include "shader_properties.hxx"

#include <string_view>
#include <tuple>
#include <vector>

namespace dreco
{
class shader_gl_base
{
public:
	shader_gl_base(const shader_properties& _p);
	~shader_gl_base();

	void Use();

	void SetUniform(const std::string_view uniform_name, const mat2x3& _m);

	int GetUniformLocation(const std::string_view uniform_name) const;

	int GetAttribLocation(const std::string_view uniform_name) const;

private:
	GLuint CompileShader(GLenum _s_type, const char* _src);
	GLuint LinkShaderProgram();

	GLuint vert_shader_id = 0;
	GLuint frag_shader_id = 0;
	GLuint program_id = 0;
};
}	 // namespace dreco