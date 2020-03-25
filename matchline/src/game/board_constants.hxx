#pragma once
#include <stdint.h>

constexpr uint8_t BOARD_WIDTH = 7;
constexpr uint8_t BOARD_HEIGHT = 10;
constexpr float BOARD_TILE_SPACE = 0.15f;
constexpr float BOARD_CENTER_OFFSET_WIDTH =
	BOARD_WIDTH % 2 == 0 ? (BOARD_WIDTH * BOARD_TILE_SPACE) / 2
						 : (BOARD_WIDTH * BOARD_TILE_SPACE) / 2 - (BOARD_TILE_SPACE / 2);
constexpr float BOARD_CENTER_OFFSET_HEIGHT =
	BOARD_WIDTH % 2 == 0 ? (BOARD_HEIGHT * BOARD_TILE_SPACE) / 2
						 : (BOARD_HEIGHT * BOARD_TILE_SPACE) / 2 - (BOARD_TILE_SPACE / 2);

constexpr float GEM_FALL_SPEED = 1.0f;

constexpr float GEM_DELAY_BEFORE_FALL = 0.11f;