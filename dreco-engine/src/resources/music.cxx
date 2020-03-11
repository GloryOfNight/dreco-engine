#include "music.hxx"
#include <iostream>

using namespace dreco;

music::music(const char* _fpath) : resource(resource_type::MUSIC)
{
    music_file = Mix_LoadMUS(_fpath);

    is_resource_loaded = music_file != nullptr;

    if (!is_resource_loaded) 
    {
        std::string error = Mix_GetError();
        std::cerr << "Failed to load file: " << Mix_GetError() << std::endl;
    }
}

music::~music()
{
    if(GetIsResourceLoaded()) 
    {
        Mix_FreeMusic(music_file);
    }
}

Mix_Music* music::GetMusic() const 
{
    return music_file;
}
