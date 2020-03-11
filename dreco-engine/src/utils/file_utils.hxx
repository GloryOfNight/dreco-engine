#pragma once
#include <string>

namespace dreco
{
class file_utils
{
public:
	static char* LoadSourceFromFile(const char* _fpath);
};
}	// namespace dreco