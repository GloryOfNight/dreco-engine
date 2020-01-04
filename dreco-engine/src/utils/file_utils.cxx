#include "file_utils.hxx"

#include <fstream>
#include <iostream>
#include <sstream>


#ifdef __ANDROID__
#include "SDL_image.h"
#else
#include "SDL2/SDL_image.h"
#endif
using namespace dreco;

std::string file_utils::LoadSourceFromFile(const char* _fpath)
{
	char* data = static_cast<char*>(SDL_LoadFile(_fpath, nullptr));

	std::string data_string(data);

	SDL_free(data);

	return data_string;
}