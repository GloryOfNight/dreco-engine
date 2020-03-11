#include "file_utils.hxx"

#include <fstream>
#include <iostream>
#include <sstream>


#ifdef __ANDROID__
#include "SDL_rwops.h"
#else
#include "SDL2/SDL_rwops.h"
#endif
using namespace dreco;

char* file_utils::LoadSourceFromFile(const char* _fpath)
{
	char* data = static_cast<char*>(SDL_LoadFile(_fpath, nullptr));
	
	return data;
}