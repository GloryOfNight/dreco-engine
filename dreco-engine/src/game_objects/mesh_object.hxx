#pragma once
#include "game_object.hxx"
#include "renderer/shader_gl_base.hxx"
#include "renderer/shader_properties.hxx"
#include "renderer/vertex.hxx"

#include <vector>

namespace dreco
{
class mesh_object : public game_object
{
public:
	mesh_object(const std::vector<float>& _verts, const shader_properties& _shader_prop);
	~mesh_object();

	inline shader_gl_base* GetShader() const;

	void Tick(const float& DeltaTime) override;

	void SetIsRendered(const bool _is_render);

	virtual void Render(const mat2x3& _m);

protected:
	virtual shader_gl_base* CreateShader(const shader_properties& _p);

private:
	bool bIsRendered = true;

	shader_gl_base* mesh_shader = nullptr;

	uint32_t vbo = 0;
};
}	// namespace dreco