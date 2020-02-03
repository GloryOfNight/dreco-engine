#pragma once

struct vertex
{
	vertex() : x(1.0f), y(1.0f), z(1.0f)
	{
	}
	
	vertex(const float& _x, const float& _y, const float& _z) : x(_x), y(_y), z(_z)
	{
	}

	float x;

	float y;

	float z;
};