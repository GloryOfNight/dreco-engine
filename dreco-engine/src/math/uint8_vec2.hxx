#pragma once
#include "stdint.h"

namespace dreco
{
struct uint8_vec2
{
public:
	uint8_vec2();
	uint8_vec2(const uint8_t _x, const uint8_t _y);

private:
	uint8_t x;
	uint8_t y;
};
}	 // namespace dreco