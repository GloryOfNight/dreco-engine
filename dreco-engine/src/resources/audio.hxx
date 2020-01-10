#pragma once
#include "resource.hxx"

#ifdef __ANDROID__
#include "SDL_audio.h"
#else
#include "SDL2/SDL_audio.h"
#endif

#include <stdint.h>
#include <string_view>
namespace dreco
{
class audio : public resource
{
public:
	audio(const std::string_view _fpath);
	virtual ~audio();

private:
	SDL_AudioDeviceID device = 0;

	uint32_t lenght;

	uint8_t* buffer;

	SDL_AudioSpec spec;
};
}	 // namespace dreco
