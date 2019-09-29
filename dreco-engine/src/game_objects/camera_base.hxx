#pragma once
#include "game_object.hxx"
#include "math/mat2x3.hxx"
#include "math/mat3x4.hpp"

namespace dreco
{
class camera_base : public game_object
{
public:
	camera_base();

	virtual void Init(game_world& _w);

	virtual void SetObjectTransform(const transform& _t) override;
	
	virtual void OnScreenSizeUpdate();

    mat2x3 GetViewMatrix() const;

    mat3x4 GetProjectionMatrix() const;

protected:
	mat2x3 CalculateViewMatrix() const;

	mat3x4 CalculateProjectionMatrix() const;

    mat2x3 view = mat2x3::identiry();

    mat3x4 projection = mat3x4(); 
};
}	// namespace dreco