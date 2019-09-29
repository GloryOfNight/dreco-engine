#pragma once
#include "vec2.hxx"
#include "mat2x3.hxx"

namespace dreco
{
struct transform
{
    transform();
    transform(vec2 _t, float _r, vec2 _s);

	vec2 translation = vec2();
	float rotation = 0.0f;
	vec2 scale = vec2(1.0, 1.0f);

    mat2x3 GetTranslationMatrix() const;
    mat2x3 GetRotationMatrix() const;
    mat2x3 GetScaleMatrix() const;
};
}	// namespace dreco