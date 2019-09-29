#include "mat3x4.hpp"

using namespace dreco;

mat3x4::mat3x4()
{
}

mat3x4 mat3x4::CreateProjectionMatrix2D(
	const float right, const float left, const float top, const float bottom)
{
	const float far = 1.0f;
	const float near = -1.0f;

	mat3x4 proj = mat3x4();

	proj.mat[0][0] = 2.0f / (right - left);
	proj.mat[1][1] = 2.0f / (top - bottom);
	proj.mat[2][2] = 2.0f / (far - near);
	proj.mat[0][3] = -((right + left) / (right - left));
	proj.mat[1][3] = -((top + bottom) / (top - bottom));
	proj.mat[2][3] = -((far + near) / (far - near));

	return proj;
}