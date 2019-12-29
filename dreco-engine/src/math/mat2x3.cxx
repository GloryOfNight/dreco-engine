#include "mat2x3.hxx"
#include "transform.hxx"

#include <cmath>

using namespace dreco;

mat2x3::mat2x3()
{
}

mat2x3 mat2x3::identiry()
{
	return mat2x3::scale(1.0f, 1.0f);
}

mat2x3 mat2x3::translate(const vec2& _v)
{
	mat2x3 r = mat2x3::identiry();

	r.mat[0][2] = _v.x;
	r.mat[1][2] = _v.y;

	return r;
}

mat2x3 mat2x3::rotate(const float& _t)
{
	mat2x3 r = mat2x3::identiry();

	const float cos_t = std::cos(_t);
	const float sin_t = std::sin(_t);

	r.mat[0][0] = cos_t;
	r.mat[0][1] = sin_t;
	r.mat[1][0] = -sin_t;
	r.mat[1][1] = cos_t;

	return r;
}

mat2x3 mat2x3::scale(const float _sx, const float _sy)
{
	mat2x3 r = mat2x3();

	r.mat[0][0] = _sx;
	r.mat[1][1] = _sy;

	return r;
}

mat2x3 mat2x3::inverse(const mat2x3& _m)
{
	const float m[3][3] = {_m.mat[0][0], _m.mat[0][1], _m.mat[0][2], _m.mat[1][0],
		_m.mat[1][1], _m.mat[1][2], 0.0f, 0.0f, 1.0f};

	double det = m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2]) -
				 m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
				 m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);

	double invdet = 1 / det;

	mat2x3 res = mat2x3();
	res.mat[0][0] = (m[1][1] * m[2][2] - m[2][1] * m[1][2]) * invdet;
	res.mat[0][1] = (m[0][2] * m[2][1] - m[0][1] * m[2][2]) * invdet;
	res.mat[0][2] = (m[0][1] * m[1][2] - m[0][2] * m[1][1]) * invdet;
	res.mat[1][0] = (m[1][2] * m[2][0] - m[1][0] * m[2][2]) * invdet;
	res.mat[1][1] = (m[0][0] * m[2][2] - m[0][2] * m[2][0]) * invdet;
	res.mat[1][2] = (m[1][0] * m[0][2] - m[0][0] * m[1][2]) * invdet;

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

mat2x3 mat2x3::GetTranslationMatrix(const transform& _t)
{
	return mat2x3::translate(_t.translation);
}

mat2x3 mat2x3::GetRotationMatrix(const transform& _t)
{
	return mat2x3::rotate(_t.rotation);
}

mat2x3 mat2x3::GetScaleMatrix(const transform& _t)
{
	return mat2x3::scale(_t.scale.x, _t.scale.y);
}