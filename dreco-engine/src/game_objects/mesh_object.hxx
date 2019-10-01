#pragma once
#include "game_object.hxx"
#include "renderer/shader_gl_base.hxx"
#include "renderer/shader_properties.hxx"
#include "renderer/vertex_properties.hxx"
#include "renderer/vertex.hxx"

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

	virtual void Render();

protected:
	inline void GenerateVBO_Vert(const std::vector<float>& _v);
	inline void GenerateVBO_TexCoord(const std::vector<float>& _tc);
	inline void GenerateTexture(const std::string& _path);

	virtual shader_gl_base* CreateShader(const shader_properties& _p);

private:
	bool bIsRendered = true;

	shader_gl_base* mesh_shader = nullptr;

	uint32_t vbo_vert = 0;
	uint32_t vbo_tc = 0;
	uint32_t texture_id = 0;
};
}	// namespace dreco