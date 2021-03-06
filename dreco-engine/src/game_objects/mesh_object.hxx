#pragma once
#include "game_object.hxx"
#include "renderer/gl_shader_base.hxx"
#include "renderer/gl_shader_info.hxx"
#include "resources/texture.hxx"
#include "renderer/mesh_data.hxx"

#include <vector>

namespace dreco
{
class mesh_object : public game_object
{
public:
	mesh_object(game_world* _w, const mesh_data* _mesh_data, const gl_shader_info& _s);
	~mesh_object();

	inline gl_shader_base* GetShader() const;

	virtual void Tick(const float& DeltaTime) override;

	bool GetIsRendered() const;

	void SetIsRendered(const bool& _v);

	void UpdateModelTransform();

	virtual void StartDraw();

	void SetTexture(texture* _t);

	bool GetIsPointInBounds(const vec2& _p) const;

protected:
	virtual void Draw();

	virtual gl_shader_base* CreateShader(const gl_shader_info& _p);

private:
	const mesh_data* mesh;

	texture* texture_ptr = nullptr;

	gl_shader_base* mesh_shader = nullptr;

	bool bIsRendered = true;
};
}	// namespace dreco