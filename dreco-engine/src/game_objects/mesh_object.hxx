#pragma once
#include "game_object.hxx"
#include "renderer/shader_gl_base.hxx"
#include "renderer/shader_properties.hxx"
#include "renderer/texture.hxx"
#include "renderer/vertex.hxx"
#include "renderer/vertex_properties.hxx"

#include <vector>

namespace dreco
{
class mesh_object : public game_object
{
public:
	mesh_object(const vertex_properties& _v, const shader_properties& _shader_prop);
	~mesh_object();

	inline shader_gl_base* GetShader() const;

	void Tick(const float& DeltaTime) override;

	void SetIsRendered(const bool _is_render);

	void UpdateModelTransform();

protected:
	virtual void Render();
	virtual void RenderTextured();

	inline void GenerateVBO_Vert(const std::vector<float>& _v);
	inline void GenerateVBO_TexCoord(const std::vector<float>& _tc);

	virtual shader_gl_base* CreateShader(const shader_properties& _p);

private:
	std::shared_ptr<texture> texture_ptr = nullptr;

	shader_gl_base* mesh_shader = nullptr;

	bool bIsRendered = true;

	uint32_t vbo_vert = 0;
	uint32_t vbo_tc = 0;
};
}	// namespace dreco