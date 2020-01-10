#include "audio_manager.hxx"

#include "engine.hxx"

#ifdef __ANDROID__
#include "SDL_mixer.h"
#else
#include "SDL2/SDL_mixer.h"
#endif

#include <iostream>

using namespace dreco;

audio_manager::audio_manager(engine& _e) : owner(&_e)
{
	const int res = Mix_OpenAudio(44100, AUDIO_S8, 2, 1024);

	if (res == -1)
	{
		std::cerr << "Mix_OpenAudio failed: " << Mix_GetError() << std::endl;
	}
}

audio_manager::~audio_manager()
{
	Mix_CloseAudio();
}

int audio_manager::GetChannels() const
{
	int channels;
	int res = Mix_QuerySpec(nullptr, nullptr, &channels);

	return res != 0 ? channels : 0;
}

void audio_manager::PlayAudio(audio& _a, int _channel, int _loops)
{
	Mix_PlayChannel(_channel, _a.GetChunk(), _loops);
}