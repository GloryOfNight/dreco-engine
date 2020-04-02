#pragma once
#include <stdint.h>

namespace dreco
{
enum resource_type : uint8_t
{
    TEXTURE = 0,
    AUDIO = 1,
    MUSIC = 2,
    SOURCE_FILE = 3
};
}