#include "audio.hxx"

#include <iostream>

using namespace dreco;

void audio_callback(void* _userdata, Uint8* stream, int len);

audio::audio(const std::string_view _fpath) : resource(resource_type::AUDIO)
{
	auto audio = SDL_LoadWAV(_fpath.cbegin(), &spec, &buffer, &lenght);

	if (audio == nullptr)
	{
		std::cerr << "Failed to load file: " << _fpath << std::endl;
		SDL_FreeWAV(buffer);
		return;
	}

	spec.callback = audio_callback;
	spec.userdata = this;

	is_resource_loaded = true;
}

audio::~audio()
{
	if (GetIsResourceLoaded())
	{
		SDL_FreeWAV(buffer);
	}
}

void audio_callback(void* _userdata, Uint8* stream, int len)
{
}