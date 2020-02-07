#pragma once
#include "game_object.hxx"
#include "math/mat2x3.hxx"

namespace dreco
{
class camera_base : public game_object
{
public:
	camera_base();

	virtual void Init(game_world& _w) override;

	virtual void SetObjectTransform(const transform& _t) override;
	
	virtual void OnScreenSizeUpdate();

    mat2x3 GetViewMatrix() const;

    mat2x3 GetProjectionMatrix() const;

protected:
	mat2x3 CalculateViewMatrix() const;

	mat2x3 CalculateProjectionMatrix() const;

    mat2x3 view;

    mat2x3 projection; 
};
}	// namespace dreco