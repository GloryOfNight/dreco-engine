#include "mat2x3.hxx"

#include <cmath>

using namespace dreco;

mat2x3::mat2x3()
{
}

mat2x3 mat2x3::translate(vec2& _v)
{
	mat2x3 r = scale(1.0f, 1.0f);

	r.c20 = _v.x;
	r.c21 = _v.y;

	return r;
}

mat2x3 mat2x3::rotate(const float& _t)
{
	mat2x3 r = mat2x3();

	const float cos_t = std::cos(_t);
	const float sin_t = std::sin(_t);

	r.c00 = cos_t;
	r.c01 = sin_t;
	r.c10 = -sin_t;
	r.c11 = cos_t;

	return r;
}

mat2x3 mat2x3::scale(const float _sx, const float _sy)
{
	mat2x3 r = mat2x3();

	r.c00 = _sx;
	r.c11 = _sy;

	return r;
}

mat2x3 operator*(const mat2x3& _m1, const mat2x3& _m2)
{
	mat2x3 r;

	r.c00 = _m1.c00 * _m2.c00 + _m1.c10 * _m2.c01;
	r.c10 = _m1.c00 * _m2.c10 + _m1.c10 * _m2.c11;
	r.c01 = _m1.c01 * _m2.c00 + _m1.c11 * _m2.c01;
	r.c11 = _m1.c01 * _m2.c10 + _m1.c11 * _m2.c11;

	r.c20 = _m1.c20 * _m2.c00 + _m1.c21 * _m2.c01 + _m2.c20;
	r.c21 = _m1.c20 * _m2.c10 + _m1.c21 * _m2.c11 + _m2.c21;

	return mat2x3();
}