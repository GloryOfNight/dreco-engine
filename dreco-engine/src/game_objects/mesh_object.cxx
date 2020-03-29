#include "mesh_object.hxx"
#ifdef __ANDROID__
#include "SDL_opengl.h"
#else
#include "SDL2/SDL_opengl.h"
#endif
#include "core/engine.hxx"
#include "game_objects/camera_base.hxx"
#include "renderer/gl_check.hxx"
#include "renderer/gl_inline_functions.hxx"

using namespace dreco;

mesh_object::mesh_object(game_world* _w, const vertex_properties& _v, const shader_properties& _s)
	: game_object(_w), vert_info(_v)
{
	GenerateVBO_Vert(_v.vertexes);
	GenerateIBO_Elem(_v.vert_elem);
	GenerateVBO_TexCoord(_v.texture_coords);

	mesh_shader = CreateShader(_s);
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

void mesh_object::GenerateIBO_Elem(const std::vector<uint8_t>& _e)
{
	glGenBuffers(1, &ibo_elem);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elem);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _e.capacity() * sizeof(uint8_t), &_e.front(),
		GL_STATIC_DRAW);
	ibo_elem_indexes = _e.capacity();
}

void mesh_object::Tick(const float& DeltaTime)
{
	game_object::Tick(DeltaTime);
}

bool mesh_object::GetIsRendered() const 
{
	return bIsRendered;
}

void mesh_object::SetIsRendered(const bool& _v)
{
	bIsRendered = _v;
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

	const mat2x3 model = mat2x3::GetModelMatrix(GetTransform());
	const mat2x3 view = GetWorld()->GetPlayerCamera()->GetViewMatrix();
	const mat2x3 modelview = view * model;
	GetShader()->SetUniform("u_modelview", modelview);

	const auto proj = GetWorld()->GetPlayerCamera()->GetProjectionMatrix();
	GetShader()->SetUniform("u_projection", proj);
}

bool mesh_object::GetIsPointInBounds(const vec2& _p) const
{
	const mat2x3 model = mat2x3::GetModelMatrix(GetTransform());

	// retrieve all mesh points
	const size_t elem_size = vert_info.vert_elem.size();
	vec2 mesh_points[elem_size];
	for (uint8_t i = 0; i < elem_size; ++i)
	{
		const uint16_t k = vert_info.vert_elem[i] * 3;
		mesh_points[i] = vec2(vert_info.vertexes[k], vert_info.vertexes[k + 1]);
	}

	// check each triangle is point in it
	for (uint8_t i = 0; i < elem_size / 3; ++i)
	{
		const vec2 a = model * mesh_points[i * 3];
		const vec2 b = model * mesh_points[i * 3 + 1];
		const vec2 c = model * mesh_points[i * 3 + 2];

		const float r1 = (a.x - _p.x) * (b.y - a.y) - (b.x - a.x) * (a.y - _p.y);
		const float r2 = (b.x - _p.x) * (c.y - b.y) - (c.x - b.x) * (b.y - _p.y);
		const float r3 = (c.x - _p.x) * (a.y - c.y) - (a.x - c.x) * (c.y - _p.y);

		if (((r1 > 0.0f && r2 > 0.0f && r3 > 0.0f) ||
				(r1 < 0.0f && r2 < 0.0f && r3 < 0.0f)) &&
			(r1 != 0.0f && r2 != 0.0f && r3 != 0.0f))
		{
			return true;
		}
	}

	return false;
}

void mesh_object::SetTexture(texture* _t)
{
	texture_ptr = _t;
}

void mesh_object::SetObjectIndex(const int& _c)
{
	obj_index = _c;
}

int mesh_object::GetObjectIndex() const
{
	return obj_index;
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
	GetShader()->Use();

	if (texture_ptr)
	{
		int is_color = GetShader()->GetUniformLocation("is_color");
		glUniform1i(is_color, 0);
		GL_CHECK()

		glActiveTexture(GL_TEXTURE0 + texture_ptr->GetTextureId());
		GL_CHECK()
		glBindTexture(GL_TEXTURE_2D, texture_ptr->GetTextureId());
		GL_CHECK()
		int u_pick_loc = GetShader()->GetUniformLocation("s_texture");
		glUniform1i(u_pick_loc, texture_ptr->GetTextureId());
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
	glDrawElements(GL_TRIANGLES, ibo_elem_indexes, GL_UNSIGNED_BYTE, 0);
	GL_CHECK()

	glDisableVertexAttribArray(a_pos_loc);
	glDisableVertexAttribArray(a_tc_loc);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	GL_CHECK()
}
