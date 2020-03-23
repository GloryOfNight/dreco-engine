#include "mat2x3.hxx"

#include "transform.hxx"

#include <math.h>

using namespace dreco;

mat2x3::mat2x3() : mat()
{
}

mat2x3::mat2x3(const float _v[2][3])
	: mat{{_v[0][0], _v[0][1], _v[0][2]}, {_v[1][0], _v[1][1], _v[1][2]}}
{
}

mat2x3 mat2x3::identiry()
{
	return mat2x3::scale(1.0f, 1.0f);
}

mat2x3 mat2x3::translate(const vec2& _v)
{
	const float v[2][3] = {{1.0f, 0.0f, _v.x}, {0.0f, 1.0f, _v.y}};
	return mat2x3(v);
}

mat2x3 mat2x3::rotate(const float& _t)
{
	const float cos_t = cos(_t);
	const float sin_t = sin(_t);

	const float v[2][3] = {{cos_t, sin_t, 0.0f}, {-sin_t, cos_t, 0.0f}};

	return mat2x3(v);
}

mat2x3 mat2x3::scale(const float& _sx, const float& _sy)
{
	const float v[2][3] = {{_sx, 0.0f, 0.0f}, {0.0f, _sy, 0.0f}};

	return mat2x3(v);
}

mat2x3 mat2x3::inverse(const mat2x3& _m)
{
	const float m[3][3] = {_m.mat[0][0], _m.mat[0][1], _m.mat[0][2], _m.mat[1][0],
		_m.mat[1][1], _m.mat[1][2], 0.0f, 0.0f, 1.0f};

	const double det = m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2]) -
					   m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
					   m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);

	const double inv_det = 1 / det;

	mat2x3 res = mat2x3();
	res.mat[0][0] = (m[1][1] * m[2][2] - m[2][1] * m[1][2]) * inv_det;
	res.mat[0][1] = (m[0][2] * m[2][1] - m[0][1] * m[2][2]) * inv_det;
	res.mat[0][2] = (m[0][1] * m[1][2] - m[0][2] * m[1][1]) * inv_det;
	res.mat[1][0] = (m[1][2] * m[2][0] - m[1][0] * m[2][2]) * inv_det;
	res.mat[1][1] = (m[0][0] * m[2][2] - m[0][2] * m[2][0]) * inv_det;
	res.mat[1][2] = (m[1][0] * m[0][2] - m[0][0] * m[1][2]) * inv_det;

	return res;
}

vec2 dreco::operator*(const mat2x3& _m, const vec2& _v)
{
	vec2 res;

	res.x = (_m.mat[0][0] * _v.x) + (_m.mat[0][1] * _v.y) + _m.mat[0][2];
	res.y = (_m.mat[1][0] * _v.x) + (_m.mat[1][1] * _v.y) + _m.mat[1][2];

	return res;
}

mat2x3 dreco::operator*(const mat2x3& _m1, const mat2x3& _m2)
{
	mat2x3 r = mat2x3();

	r.mat[0][0] = _m1.mat[0][0] * _m2.mat[0][0] + _m1.mat[1][0] * _m2.mat[0][1];
	r.mat[1][0] = _m1.mat[0][0] * _m2.mat[1][0] + _m1.mat[1][0] * _m2.mat[1][1];
	r.mat[0][1] = _m1.mat[0][1] * _m2.mat[0][0] + _m1.mat[1][1] * _m2.mat[0][1];
	r.mat[1][1] = _m1.mat[0][1] * _m2.mat[1][0] + _m1.mat[1][1] * _m2.mat[1][1];

	r.mat[0][2] =
		_m1.mat[0][0] * _m2.mat[0][2] + _m1.mat[0][1] * _m2.mat[1][2] + _m1.mat[0][2];
	r.mat[1][2] =
		_m1.mat[1][0] * _m2.mat[0][2] + _m1.mat[1][1] * _m2.mat[1][2] + _m1.mat[1][2];

	return r;
}

mat2x3 mat2x3::GetModelMatrix(const transform& _t)
{
	return GetTranslationMatrix(_t.translation) * GetRotationMatrix(_t.rotation) *
		   GetScaleMatrix(_t.scale);
}

mat2x3 mat2x3::GetTranslationMatrix(const vec2& _tr)
{
	return mat2x3::translate(_tr);
}

mat2x3 mat2x3::GetRotationMatrix(const float& _rot)
{
	return mat2x3::rotate(_rot);
}

mat2x3 mat2x3::GetScaleMatrix(const vec2& _sc)
{
	return mat2x3::scale(_sc.x, _sc.y);
}