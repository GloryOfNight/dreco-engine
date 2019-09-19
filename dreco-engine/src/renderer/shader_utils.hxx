#pragma once
#include <string>

namespace dreco
{
class shader_utils
{
public:
	static std::string LoadShaderSource(const char* _fpath);
};
}	// namespace dreco