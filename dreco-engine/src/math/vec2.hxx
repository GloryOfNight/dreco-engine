#pragma once

namespace dreco
{
struct vec2
{
	vec2();

	vec2(const float _x, const float _y);

	float x = 0.0f;
	float y = 0.0f;

	const void operator*=(const vec2& _v);

	const vec2 operator*(const vec2& _v);

	const void operator-=(const float& _f);
	
	const void operator+=(const float& _f);
};
}	// namespace dreco