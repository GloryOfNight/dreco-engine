#pragma once
#include "stdint.h"

enum cell_states : uint8_t 
{
    empty = 0,
    recieving = 1,
    stationary = 2,
};