#pragma once
#include "game_object.hxx"
#include "renderer/shader_gl_base.hxx"
#include "renderer/shader_properties.hxx"
#include "resources/texture.hxx"
#include "renderer/vertex.hxx"
#include "renderer/vertex_properties.hxx"

#include <vector>

namespace dreco
{
class mesh_object : public game_object
{
public:
	mesh_object(game_world* _w, const vertex_properties& _v, const shader_properties& _s);
	~mesh_object();

	inline shader_gl_base* GetShader() const;

	virtual void Tick(const float& DeltaTime) override;

	bool GetIsRendered() const;

	void SetIsRendered(const bool& _v);

	void UpdateModelTransform();

	virtual void StartDraw();

	void SetTexture(texture* _t);

	bool GetIsPointInBounds(const vec2& _p) const;

protected:
	virtual void Draw();

	inline void GenerateVBO_Vert(const std::vector<float>& _v);
	inline void GenerateVBO_TexCoord(const std::vector<float>& _tc);
	inline void GenerateIBO_Elem(const std::vector<uint8_t>& _e);

	virtual shader_gl_base* CreateShader(const shader_properties& _p);

private:
	vertex_properties vert_info;

	texture* texture_ptr = nullptr;

	shader_gl_base* mesh_shader = nullptr;

	bool bIsRendered = true;

	GLuint vbo_vert = 0;
	GLuint vbo_tc = 0;
	GLuint ibo_elem = 0;

	GLubyte ibo_elem_indexes = 0;
};
}	// namespace dreco