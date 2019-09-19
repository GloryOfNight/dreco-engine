#include "shader_gl_base.hxx"
#include "gl_check.hxx"
#include "gl_inline_functions.hxx"

using namespace dreco;

shader_gl_base::shader_gl_base(const char& _v_src, const char& _f_src, const glShaderAtributes& _a) 
{  
    vert_shader_id = CompileShader(GL_VERTEX_SHADER, &_v_src);
    frag_shader_id = CompileShader(GL_FRAGMENT_SHADER, &_f_src);

    if (vert_shader_id == 0 || frag_shader_id == 0) 
    {
        std::cerr << "Compilation failed;" << std::endl;
        return;
    }

    program_id = LinkShaderProgram(_a);
}

void shader_gl_base::Use() 
{
    glUseProgram(program_id);
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

        std::cerr << "Error compiling shader: " << shader_type_name << ". With: \n" << info_log.data();
     
        return 0;
    }

    return shader_id;
}

GLuint shader_gl_base::LinkShaderProgram(const glShaderAtributes& _a) 
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


    for (const auto& attr : _a)
    {
        GLuint        loc  = std::get<0>(attr);
        const GLchar* name = std::get<1>(attr);
        glBindAttribLocation(local_program_id, loc, name);
        GL_CHECK();
    }

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