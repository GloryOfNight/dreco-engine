#pragma once
#include "vec2.hxx"

namespace dreco
{
struct mat2x3
{
	mat2x3();

	float mat[2][3] = {0};

	static mat2x3 identiry();

	static mat2x3 translate(const vec2& _v);

	static mat2x3 rotate(const float& _t);

	static mat2x3 scale(const float _sx, const float _sy);
};
mat2x3 operator*(const mat2x3& _m1, const mat2x3& _m2);
}	// namespace dreco
