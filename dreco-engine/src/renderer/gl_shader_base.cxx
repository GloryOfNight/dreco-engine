#include "gl_shader_base.hxx"

#include "gl_check.hxx"
#include "gl_inline_functions.hxx"
#include "resources/file_source.hxx"

using namespace dreco;

gl_shader_base::gl_shader_base(const gl_shader_info& _info, resource_manager* _rm)
{
	const char* shader_source;
	size_t shader_size;

	_rm->GetFileSource(_info.vertex_shader_path, &shader_source, &shader_size);
	if (shader_source)
		vert_shader_id = CompileShader(GL_VERTEX_SHADER, shader_source, &shader_size);
		
	_rm->GetFileSource(_info.fragment_shader_path, &shader_source, &shader_size);
	if (shader_source)
		frag_shader_id = CompileShader(GL_FRAGMENT_SHADER, shader_source, &shader_size);

	program_id = LinkShaderProgram();
}

gl_shader_base::~gl_shader_base()
{
	glDeleteShader(vert_shader_id);
	glDeleteShader(frag_shader_id);
	glDeleteProgram(program_id);
}

void gl_shader_base::Use()
{
	glUseProgram(program_id);
}

void gl_shader_base::SetUniform(const char* uniform_name, const mat2x3& _m)
{
	const int u_loc = glGetUniformLocation(program_id, uniform_name);

	if (u_loc == -1)
	{
		std::cerr << "SetUniform(): Couldn't get uniform: " << std::string(uniform_name)
				  << std::endl;
		return;
	}

	// clang-format off
	float mat3x3_array[9] = {_m.mat[0][0], _m.mat[0][1], _m.mat[0][2], 
							_m.mat[1][0], _m.mat[1][1], _m.mat[1][2], 
							0.0f, 0.0f, 1.0f};
	// clang-format on
	glUniformMatrix3fv(u_loc, 1, GL_FALSE, mat3x3_array);
}

int gl_shader_base::GetUniformLocation(const char* uniform_name) const
{
	return glGetUniformLocation(program_id, uniform_name);
}

int gl_shader_base::GetAttribLocation(const char* uniform_name) const
{
	return glGetAttribLocation(program_id, uniform_name);
}

GLuint gl_shader_base::CompileShader(
	GLenum _s_type, const char* _src, const size_t* _size)
{
	GLuint shader_id = glCreateShader(_s_type);
	const GLchar* src = _src;

	glShaderSource(shader_id, 1, &src, nullptr);
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
		char info_log[info_len];
		glGetShaderInfoLog(shader_id, info_len, nullptr, info_log);
		GL_CHECK();
		glDeleteShader(shader_id);
		GL_CHECK();
		const char* shader_type_name =
			_s_type == GL_VERTEX_SHADER ? "vertex" : "fragment";

		std::cerr << "Error compiling shader: " << shader_type_name << ". With: \n"
				  << info_log;

		return 0;
	}

	return shader_id;
}

GLuint gl_shader_base::LinkShaderProgram()
{
	GLuint local_program_id = glCreateProgram();
	GL_CHECK();

	if (local_program_id == GL_FALSE)
	{
		throw std::runtime_error("Failed to glCreateProgram(), can't link program");
	}

	if (GL_FALSE != vert_shader_id)
		glAttachShader(local_program_id, vert_shader_id);
	GL_CHECK();
	if (GL_FALSE != frag_shader_id)
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