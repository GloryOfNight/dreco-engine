#include "audio.hxx"

#include <iostream>

using namespace dreco;

audio::audio(const char* _fpath) : resource(resource_type::AUDIO)
{
	chunk = Mix_LoadWAV(_fpath);
	
	is_resource_loaded = chunk != nullptr;

	if (!is_resource_loaded)
	{
		std::cerr << "Failed to load file: " << Mix_GetError() << std::endl;
	}	
}

audio::~audio()
{
	if (GetIsResourceLoaded())
	{
		Mix_FreeChunk(chunk);
	}
}

Mix_Chunk* audio::GetChunk() const 
{
	return chunk;
}