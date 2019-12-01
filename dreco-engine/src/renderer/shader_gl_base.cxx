#include "shader_gl_base.hxx"

#include "gl_check.hxx"
#include "gl_inline_functions.hxx"

using namespace dreco;

shader_gl_base::shader_gl_base(const shader_properties& _p)
{
	vert_shader_id = CompileShader(GL_VERTEX_SHADER, _p.vert_src);
	frag_shader_id = CompileShader(GL_FRAGMENT_SHADER, _p.frag_src);

	if (vert_shader_id == 0 || frag_shader_id == 0)
	{
		std::cerr << "Compilation failed;" << std::endl;
		return;
	}

	program_id = LinkShaderProgram();
}

shader_gl_base::~shader_gl_base()
{
	glDeleteShader(vert_shader_id);
	glDeleteShader(frag_shader_id);
	glDeleteProgram(program_id);
}

void shader_gl_base::Use()
{
	glUseProgram(program_id);
}

void shader_gl_base::SetUniform(const std::string_view uniform_name, const mat2x3& _m)
{
	const int u_loc = glGetUniformLocation(program_id, uniform_name.cbegin());

	if (u_loc == -1)
	{
		std::cerr << "SetUniform(): Couldn't get uniform: " << uniform_name << std::endl;
		return;
	}

	// clang-format off
	float mat3x3_array[9] = {_m.mat[0][0], _m.mat[0][1], _m.mat[0][2], 
							_m.mat[1][0], _m.mat[1][1], _m.mat[1][2], 
							0.0f, 0.0f, 1.0f};
	// clang-format on
	glUniformMatrix3fv(u_loc, 1, GL_FALSE, mat3x3_array);
}

int shader_gl_base::GetUniformLocation(const std::string_view uniform_name) const
{
	return glGetUniformLocation(program_id, uniform_name.cbegin());
}

int shader_gl_base::GetAttribLocation(const std::string_view uniform_name) const
{
	return glGetAttribLocation(program_id, uniform_name.cbegin());
}

GLuint shader_gl_base::CompileShader(GLenum _s_type, const char* _src)
{
	GLuint shader_id = glCreateShader(_s_type);

	glShaderSource(shader_id, 1, &_src, nullptr);
	GL_CHECK();

	glCompileShader(shader_id);
	GL_CHECK();

	GLint compile_status = 0;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_status);

	if (compile_status == GL_FALSE)
	{
		GLint info_len = 0;
		glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_len);
		GL_CHECK();
		std::vector<char> info_log(static_cast<size_t>(info_len));
		glGetShaderInfoLog(shader_id, info_len, nullptr, info_log.data());
		GL_CHECK();
		glDeleteShader(shader_id);
		GL_CHECK();
		const std::string shader_type_name =
			_s_type == GL_VERTEX_SHADER ? "vertex" : "fragment";

		std::cerr << "Error compiling shader: " << shader_type_name << ". With: \n"
				  << info_log.data();

		return 0;
	}

	return shader_id;
}

GLuint shader_gl_base::LinkShaderProgram()
{
	GLuint local_program_id = glCreateProgram();
	GL_CHECK();

	if (local_program_id == GL_FALSE)
	{
		throw std::runtime_error("Failed to glCreateProgram(), can't link program");
	}

	glAttachShader(local_program_id, vert_shader_id);
	GL_CHECK();
	glAttachShader(local_program_id, frag_shader_id);
	GL_CHECK();

	glLinkProgram(local_program_id);

	GLint link_status = 0;
	glGetProgramiv(local_program_id, GL_LINK_STATUS, &link_status);
	GL_CHECK();

	if (link_status == GL_FALSE)
	{
		GLint log_len = 0;
		glGetProgramiv(local_program_id, GL_INFO_LOG_LENGTH, &log_len);
		GL_CHECK();

		std::vector<char> info_log(static_cast<size_t>(log_len));
		glGetProgramInfoLog(local_program_id, log_len, NULL, info_log.data());
		GL_CHECK();

		glDeleteProgram(local_program_id);
		GL_CHECK();

		std::cerr << "Error linking program with error: " << info_log.data() << std::endl;
		throw std::runtime_error("LinkShaderProgram() ERROR: Can't link program");

		return 0;
	}

	return local_program_id;
}