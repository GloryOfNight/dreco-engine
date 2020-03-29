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

void file_utils::LoadSourceFromFile(const char* _file_path, char* _out_src, size_t* _out_len)
{
	_out_src = static_cast<char*>(SDL_LoadFile(_file_path, _out_len));
}