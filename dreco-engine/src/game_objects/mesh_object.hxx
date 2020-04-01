#pragma once
#include "game_object.hxx"
#include "renderer/shader_gl_base.hxx"
#include "renderer/shader_properties.hxx"
#include "resources/texture.hxx"
#include "renderer/mesh_data.hxx"
#include "renderer/vertex.hxx"
#include "renderer/vertex_properties.hxx"

#include <vector>

namespace dreco
{
class mesh_object : public game_object
{
public:
	mesh_object(game_world* _w, const mesh_data* _mesh_data, const shader_properties& _s);
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

	virtual shader_gl_base* CreateShader(const shader_properties& _p);

private:
	const mesh_data* mesh;

	texture* texture_ptr = nullptr;

	shader_gl_base* mesh_shader = nullptr;

	bool bIsRendered = true;
};
}	// namespace dreco