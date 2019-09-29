#include "mesh_object.hxx"

#include "SDL2/SDL_opengl.h"
#include "core/engine.hxx"
#include "game_objects/camera_base.hxx"
#include "renderer/gl_check.hxx"
#include "renderer/gl_inline_functions.hxx"

using namespace dreco;

mesh_object::mesh_object(
	const std::vector<float>& _verts, const shader_properties& _shader_prop)
{
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, _verts.capacity() * sizeof(float), &_verts.front(),
		GL_STATIC_DRAW);

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
	if (bIsRendered)
	{
		UpdateModelTransform();
		Render();
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

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	int size;
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);

	glDrawArrays(GL_TRIANGLES, 0, size / sizeof(float));

	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}