#pragma once
#include <string>

namespace dreco
{
class file_utils
{
public:
	static std::string LoadSourceFromFile(const char* _fpath);
};
}	// namespace dreco