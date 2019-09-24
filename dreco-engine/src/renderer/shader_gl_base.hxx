#pragma once
#include "SDL2/SDL_opengl.h"
#include "math/mat2x3.hxx"

#include <tuple>
#include <vector>

namespace dreco
{
typedef std::vector<std::tuple<GLuint, const GLchar*>> glShaderAtributes;

class shader_gl_base
{
public:
	shader_gl_base(const char& _v_src, const char& _f_src, const glShaderAtributes& _a);
	~shader_gl_base();

	void Use();

	void SetUniform(const std::string_view uniform_name, const mat2x3& _m);

private:
	GLuint CompileShader(GLenum _s_type, const char* _src);
	GLuint LinkShaderProgram(const glShaderAtributes& _a);

	GLuint vert_shader_id = 0;
	GLuint frag_shader_id = 0;
	GLuint program_id = 0;
};
}	// namespace dreco