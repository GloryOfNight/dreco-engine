#pragma once

namespace dreco
{
struct mat3x4
{
	mat3x4();

	float mat[3][4] = {0};

	static mat3x4 CreateProjectionMatrix2D(
		const float right, const float left, const float top, const float bottom);
};
}	// namespace dreco