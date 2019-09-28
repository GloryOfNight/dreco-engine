#include "mesh_object.hxx"

#include "SDL2/SDL_opengl.h"
#include "core/engine.hxx"
#include "glm/gtc/matrix_transform.hpp"
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

	mat2x3 mat = t.GetRotationMatrix() * t.GetTranslationMatrix() * t.GetScaleMatrix();

	GetShader()->SetUniform("u_matrix", mat);

	int w, h;
	SDL_GetWindowSize(GetGameInstance()->GetEngine()->GetWindow(), &w, &h);

	const float aspect_ratio = static_cast<float>(w) / static_cast<float>(h);

	// TODO BEGIN
	// Refactor Projection things to special camera class
	float scale_factor = 1.0f;
	if (aspect_ratio < 0.5625f)
	{
		scale_factor = (aspect_ratio / 0.5625f);
	}

	mat3x4 proj = CreateProjectionMatrix(aspect_ratio / scale_factor,
		-aspect_ratio / scale_factor, 1.0f / scale_factor, -1.0f / scale_factor);
	// TODO END
	
	GetShader()->SetUniform("u_projection", proj);
}

mat3x4 mesh_object::CreateProjectionMatrix(
	const float right, const float left, const float top, const float bottom)
{
	const float far = 1.0f;
	const float near = -1.0f;

	mat3x4 proj = mat3x4();

	proj.mat[0][0] = 2.0f / (right - left);
	proj.mat[1][1] = 2.0f / (top - bottom);
	proj.mat[2][2] = 2.0f / (far - near);
	proj.mat[0][3] = -((right + left) / (right - left));
	proj.mat[1][3] = -((top + bottom) / (top - bottom));
	proj.mat[2][3] = -((far + near) / (far - near));

	return proj;
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