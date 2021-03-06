#include "math_utils.hxx"

using namespace dreco;

vec2 math_utils::UnProject(const vec2& _screen_coord, const vec2& _viewport_size,
	const mat2x3& _v, const mat2x3& _p)
{
	const mat2x3 inv_pv = mat2x3::inverse(_p * _v);

	vec2 in{((2 * _screen_coord.x) / _viewport_size.x) - 1,
		1 - ((2 * _screen_coord.y) / _viewport_size.y)};

	return inv_pv * in;
}

mat2x3 math_utils::CreateProjectionMatrix2D(
	const float right, const float left, const float top, const float bottom)
{
	mat2x3 proj = mat2x3::identiry();

	proj.mat[0][0] = 2.0f / (right - left);
	proj.mat[1][1] = 2.0f / (top - bottom);

	return proj;
}