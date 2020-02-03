#include "vec3.hxx"

#include "mat2x3.hxx"

using namespace dreco;

vec3::vec3() : x(0.0f), y(0.0f), z(0.0f)
{
}

vec3::vec3(const float& _x, const float& _y, const float& _z) : x(_x), y(_y), z(_z)
{
}

vec3 vec3::operator*(const mat2x3& _m)
{
	vec3 res;
	res.x = x * _m.mat[0][0] + x * _m.mat[1][0];
	res.y = y * _m.mat[0][1] + y * _m.mat[1][1];
	res.z = z * _m.mat[0][2] + z * _m.mat[1][2] + res.z;
	return res;
}