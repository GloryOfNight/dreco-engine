#pragma once

struct vertex
{
	vertex()
	{
	}
	vertex(const float _x, const float _y, const float _z) : x(_x), y(_y), z(_z)
	{
	}

	float x = 1.0f;
	float y = 1.0f;
	float z = 1.0f;
};