#pragma once
#include "stdint.h"

namespace dreco
{
struct int_vec2
{
public:
	int_vec2();
	
	int_vec2(const int32_t _x, const int32_t _y);

	int32_t x;
	int32_t y;

	int_vec2 operator-(const int_vec2& _v);
};
}	 // namespace dreco