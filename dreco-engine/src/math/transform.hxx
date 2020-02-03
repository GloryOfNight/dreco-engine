#pragma once
#include "vec2.hxx"
#include "mat2x3.hxx"

namespace dreco
{
struct transform
{
    transform();

    transform(const vec2& _t, const float& _r, const vec2& _s);

	vec2 translation;

	float rotation;

	vec2 scale;
};
}	// namespace dreco