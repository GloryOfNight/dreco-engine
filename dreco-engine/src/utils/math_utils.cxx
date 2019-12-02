#include "math_utils.hxx"

using namespace dreco;

vec2 math_utils::UnProject(const vec2& _screen_coord, const vec2& _viewport_size, 
			const mat2x3& _v, const mat2x3& _p)
{
    mat2x3 vp = _v * _p;
	vp = mat2x3::inverse(vp);

	vec3 in;
	in.x = 	((_screen_coord.x / _viewport_size.x) * 2) - 1.0f;
	in.y = 1.0f - ((_screen_coord.y / _viewport_size.y) * 2);
	in.z = 1;

	vec2 res;
    res.x = in.x *vp.mat[0][0] + in.x *vp.mat[1][0] + vp.mat[0][2];
    res.y = in.y * vp.mat[0][1] + in.y * vp.mat[1][1] + vp.mat[1][2];

	return res;
}

mat2x3 math_utils::CreateProjectionMatrix2D(
	const float right, const float left, const float top, const float bottom)
{
	const float far = 1.0f;
	const float near = -1.0f;

	mat2x3 proj = mat2x3::identiry();

	proj.mat[0][0] = 2.0f / (right - left);
	proj.mat[1][1] = 2.0f / (top - bottom);
	proj.mat[2][2] = 2.0f / (far - near);

	return proj;
}