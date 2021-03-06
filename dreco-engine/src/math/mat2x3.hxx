#pragma once
#include "vectors.hxx"

namespace dreco
{
struct transform;

struct mat2x3
{
	mat2x3();

	mat2x3(const float _v[2][3]);

	static mat2x3 identiry();

	static mat2x3 translate(const vec2& _v);

	static mat2x3 rotate(const float& _t);

	static mat2x3 scale(const float& _sx, const float& _sy);

	static mat2x3 inverse(const mat2x3& _m);

	static mat2x3 GetModelMatrix(const transform& _t);

	static mat2x3 GetTranslationMatrix(const vec2& _t);

	static mat2x3 GetRotationMatrix(const float& _t);

	static mat2x3 GetScaleMatrix(const vec2& _t);

	float mat[2][3];
};

vec2 operator*(const mat2x3& _m, const vec2& _v);

mat2x3 operator*(const mat2x3& _m1, const mat2x3& _m2);
}	 // namespace dreco
