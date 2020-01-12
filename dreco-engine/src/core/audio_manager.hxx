#pragma once
#include "resources/audio.hxx"
#include "resources/music.hxx"

namespace dreco
{
class engine;

class audio_manager
{
public:
	audio_manager(engine& _e);
	~audio_manager();

	int GetChannels() const;

    void PlayAudio(audio& _a, int _channel, int _loops);

	void PlayMusic(const music& _m);
private:
	engine* owner;
};
}	 // namespace dreco