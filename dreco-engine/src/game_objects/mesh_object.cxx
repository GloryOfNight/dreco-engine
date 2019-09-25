#include "mesh_object.hxx"
#include "SDL2/SDL_opengl.h"
#include "renderer/gl_inline_functions.hxx"
#include "renderer/gl_check.hxx"

using namespace dreco;

mesh_object::mesh_object(const std::vector<float>& _verts, const shader_properties& _shader_prop)
{
    glGenBuffers(1, &vbo);
	
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
	glBufferData(GL_ARRAY_BUFFER, _verts.capacity() * sizeof(float), &_verts.front(), GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	mesh_shader = CreateShader(_shader_prop);
}

mesh_object::~mesh_object() 
{	
	delete mesh_shader;
    glDeleteBuffers(1, &vbo);
}

void mesh_object::Tick(const float& DeltaTime)
{
	// if (bIsRendered)
	// 	Render();
}

void mesh_object::SetIsRendered(const bool _is_render)
{
	bIsRendered = !_is_render;
}

inline shader_gl_base* mesh_object::GetShader() const
{
	return mesh_shader;
}

shader_gl_base* mesh_object::CreateShader(const shader_properties& _p)
{
	return new shader_gl_base(_p);
}

void mesh_object::Render(const mat2x3& _m)
{
	GetShader()->Use();
	GetShader()->SetUniform("u_matrix", _m);
	
	glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	int size;
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);

	glDrawArrays(GL_TRIANGLES, 0, size/sizeof(float));

	glDisableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}