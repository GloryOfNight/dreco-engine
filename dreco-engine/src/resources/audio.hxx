#pragma once
#include "resource.hxx"

#ifdef __ANDROID__
#include "SDL_mixer.h"
#else
#include "SDL2/SDL_mixer.h"
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

	Mix_Chunk* GetChunk() const;
private:
	Mix_Chunk* chunk;
};
}	 // namespace dreco
