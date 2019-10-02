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
	GenerateVBO_TexCoord(_v.texture_coords);
	texture_ptr = _v.texture_ptr;

	mesh_shader = CreateShader(_shader_prop);
}

mesh_object::~mesh_object()
{
	delete mesh_shader;
	glDeleteBuffers(1, &vbo_vert);
	glDeleteBuffers(1, &vbo_tc);
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

void mesh_object::Tick(const float& DeltaTime)
{
	if (bIsRendered)
	{
		UpdateModelTransform();

		texture_ptr != nullptr ? RenderTextured() : Render();
	}
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

	mat2x3 model = t.GetRotationMatrix() * t.GetTranslationMatrix() * t.GetScaleMatrix();
	GetShader()->SetUniform("u_model", model);

	mat2x3 view = GetWorld()->GetPlayerCamera()->GetViewMatrix();
	GetShader()->SetUniform("u_view", view);

	mat3x4 proj = GetWorld()->GetPlayerCamera()->GetProjectionMatrix();
	GetShader()->SetUniform("u_projection", proj);
}

void mesh_object::Render()
{
	GetShader()->Use();

	int a_pos_loc = GetShader()->GetAttribLocation("a_position");

	glEnableVertexAttribArray(a_pos_loc);
	GL_CHECK()
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vert);
	GL_CHECK()
	glVertexAttribPointer(a_pos_loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	GL_CHECK()
	int size;
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	GL_CHECK()
	glDrawArrays(GL_TRIANGLES, 0, size / sizeof(float));
	GL_CHECK()
	glDisableVertexAttribArray(a_pos_loc);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void mesh_object::RenderTextured()
{
	glActiveTexture(GL_TEXTURE0 + texture_ptr->GetTextureId());
	GL_CHECK()
	glBindTexture(GL_TEXTURE_2D, texture_ptr->GetTextureId());
	GL_CHECK()
	int u_t_loc = GetShader()->GetUniformLocation("s_texture");
	glUniform1i(u_t_loc, texture_ptr->GetTextureId());
	GL_CHECK()

	int a_tc_loc = GetShader()->GetAttribLocation("a_tex_coord");
	glBindBuffer(GL_ARRAY_BUFFER, vbo_tc);
	GL_CHECK()
	glEnableVertexAttribArray(a_tc_loc);
	GL_CHECK()
	glVertexAttribPointer(a_tc_loc, 2, GL_FLOAT, GL_FALSE, 0, 0);
	GL_CHECK()

	int a_pos_loc = GetShader()->GetAttribLocation("a_position");
	glEnableVertexAttribArray(a_pos_loc);
	GL_CHECK()
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vert);
	GL_CHECK()
	glVertexAttribPointer(a_pos_loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	GL_CHECK()
	int size;
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	GL_CHECK()
	glDrawArrays(GL_TRIANGLES, 0, size / sizeof(float));
	GL_CHECK()

	glDisableVertexAttribArray(a_tc_loc);
	glDisableVertexAttribArray(a_pos_loc);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}