#include "audio.hxx"

#include <iostream>

using namespace dreco;

audio::audio(const std::string_view& _fpath) : resource(resource_type::AUDIO)
{
	chunk = Mix_LoadWAV(_fpath.cbegin());
	
	is_resource_loaded = chunk != nullptr;

	if (!is_resource_loaded)
	{
		std::cerr << "Failed to load file: " << _fpath << std::endl;
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