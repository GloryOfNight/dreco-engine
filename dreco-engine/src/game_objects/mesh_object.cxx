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
	if (_v.texture_path.length() > 0)
	{
		GenerateVBO_TexCoord(_v.texture_coords);
		GenerateTexture(_v.texture_path);
	}

	mesh_shader = CreateShader(_shader_prop);
}

mesh_object::~mesh_object()
{
	delete mesh_shader;
	glDeleteBuffers(1, &vbo_vert);

	if (texture_id > 0)
	{
		glDeleteBuffers(1, &vbo_tc);
		glDeleteTextures(1, &texture_id);
	}
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

void mesh_object::GenerateTexture(const std::string& _path)
{
	SDL_Surface* res_texture = IMG_Load(_path.c_str());

	if (!res_texture)
	{
		std::cerr << "GenerateTexture(): Invalid path: " << _path << std::endl;
		return;
	}

	glGenTextures(1, &texture_id);
	GL_CHECK();

	glBindTexture(GL_TEXTURE_2D, texture_id);
	GL_CHECK();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	GL_CHECK();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, res_texture->w, res_texture->h, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, res_texture->pixels);
	GL_CHECK();

	SDL_FreeSurface(res_texture);
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

	if (texture_id > 0)
	{
		glActiveTexture(GL_TEXTURE0 + texture_id);
		GL_CHECK()
		glBindTexture(GL_TEXTURE_2D, texture_id);
		GL_CHECK()
		int t_loc = GetShader()->GetUniformLocation("s_texture");
		glUniform1i(t_loc, texture_id);
		GL_CHECK()

		int tc_loc = GetShader()->GetAttribLocation("a_tex_coord");
		glBindBuffer(GL_ARRAY_BUFFER, vbo_tc);
		GL_CHECK()
		glEnableVertexAttribArray(tc_loc);
		GL_CHECK()
		glVertexAttribPointer(tc_loc, 2, GL_FLOAT, GL_FALSE, 0, 0);
		GL_CHECK()
	}

	int pos_loc = GetShader()->GetAttribLocation("a_position");

	glEnableVertexAttribArray(pos_loc);
	GL_CHECK()
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vert);
	GL_CHECK()
	glVertexAttribPointer(pos_loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	GL_CHECK()
	int size;
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	GL_CHECK()
	glDrawArrays(GL_TRIANGLES, 0, size / sizeof(float));
	GL_CHECK()
	glDisableVertexAttribArray(pos_loc);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}