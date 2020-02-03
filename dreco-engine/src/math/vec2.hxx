#pragma once

namespace dreco
{
struct vec2
{
	vec2();

	vec2(const float& _x, const float& _y);

	void operator*=(const vec2& _v);

	vec2 operator*(const vec2& _v);

	vec2 operator-(const vec2& _v);

	void operator+=(const vec2& _v);

	void operator-=(const float& _f);

	void operator+=(const float& _f);

	bool operator==(const vec2& _v);

	float x;

	float y;
};
}	 // namespace dreco