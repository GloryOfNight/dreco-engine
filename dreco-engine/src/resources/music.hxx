#pragma once
#include "resource.hxx"

#ifdef __ANDROID__
#include "SDL_mixer.h"
#else
#include "SDL2/SDL_mixer.h"
#endif

#include <string_view>

namespace dreco
{
class music : public resource
{
public:
	music(const std::string_view& _fpath);
	~music();

	Mix_Music* GetMusic() const;

private:
	Mix_Music* music_file;
};
}	 // namespace dreco