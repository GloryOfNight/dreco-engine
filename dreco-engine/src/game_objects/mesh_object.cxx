#include "mesh_object.hxx"

#include "SDL2/SDL_image.h"
#include "SDL2/SDL_opengl.h"
#include "core/engine.hxx"
#include "game_objects/camera_base.hxx"
#include "renderer/gl_check.hxx"
#include "renderer/gl_inline_functions.hxx"

using namespace dreco;

mesh_object::mesh_object(
	const vertex_properties& _v, const shader_properties& _shader_prop)
{
	GenerateVBO_Vert(_v.vertexes);
	GenerateIBO_Elem(_v.vert_elem);
	GenerateVBO_TexCoord(_v.texture_coords);
	texture_ptr = _v.texture_ptr;

	mesh_shader = CreateShader(_shader_prop);
}

mesh_object::~mesh_object()
{
	delete mesh_shader;
	const uint32_t buff[] = {vbo_vert, vbo_tc, ibo_elem};
	glDeleteBuffers(sizeof(buff) / sizeof(uint32_t), buff);
}

void mesh_object::GenerateVBO_Vert(const std::vector<float>& _v)
{
	glGenBuffers(1, &vbo_vert);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vert);
	glBufferData(
		GL_ARRAY_BUFFER, _v.capacity() * sizeof(float), &_v.front(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void mesh_object::GenerateVBO_TexCoord(const std::vector<float>& _tc)
{
	glGenBuffers(1, &vbo_tc);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_tc);
	glBufferData(
		GL_ARRAY_BUFFER, _tc.capacity() * sizeof(float), &_tc.front(), GL_STATIC_DRAW);
}

void mesh_object::GenerateIBO_Elem(const std::vector<uint32_t>& _e) 
{
	glGenBuffers(1, &ibo_elem);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elem);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _e.capacity() * sizeof(uint32_t), &_e.front(), GL_STATIC_DRAW);
}

void mesh_object::Tick(const float& DeltaTime)
{
	
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

void mesh_object::UpdateModelTransform()
{
	GetShader()->Use();

	transform t = GetObjectTransform();

	const mat2x3 model = t.GetRotationMatrix() * t.GetTranslationMatrix() * t.GetScaleMatrix();
	const mat2x3 view = GetWorld()->GetPlayerCamera()->GetViewMatrix();
	const mat2x3 modelview = model * view;
	GetShader()->SetUniform("u_modelview", modelview);

	mat3x4 proj = GetWorld()->GetPlayerCamera()->GetProjectionMatrix();
	GetShader()->SetUniform("u_projection", proj);
}

void mesh_object::StartDraw() 
{
	if (bIsRendered) 
	{
		UpdateModelTransform();
		Draw();
	}
}

void mesh_object::Draw() 
{	
	if (texture_ptr) 
	{
		glActiveTexture(GL_TEXTURE0 + texture_ptr->GetTextureId());
		GL_CHECK()
		glBindTexture(GL_TEXTURE_2D, texture_ptr->GetTextureId());
		GL_CHECK()
		int u_t_loc = GetShader()->GetUniformLocation("s_texture");
		glUniform1i(u_t_loc, texture_ptr->GetTextureId());
		GL_CHECK()
	}

	int a_tc_loc = GetShader()->GetAttribLocation("a_tex_coord");
	glBindBuffer(GL_ARRAY_BUFFER, vbo_tc);
	GL_CHECK()
	glEnableVertexAttribArray(a_tc_loc);
	GL_CHECK()
	glVertexAttribPointer(a_tc_loc, 2, GL_FLOAT, GL_FALSE, 0, 0);
	GL_CHECK()

	glBindBuffer(GL_ARRAY_BUFFER, vbo_vert);
	GL_CHECK()
	int a_pos_loc = GetShader()->GetAttribLocation("a_position");
	glVertexAttribPointer(a_pos_loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	GL_CHECK()
	glEnableVertexAttribArray(a_pos_loc);
	GL_CHECK()

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elem);
	int size;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	GL_CHECK()
	glDrawElements(GL_TRIANGLES, size/sizeof(uint32_t), GL_UNSIGNED_INT, 0);
	GL_CHECK()

	glDisableVertexAttribArray(a_tc_loc);
	glDisableVertexAttribArray(a_pos_loc);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	GL_CHECK()
}
