#pragma once
#include <string>

namespace dreco
{
class file_utils
{
public:
	static void LoadSourceFromFile(
		const char* _file_path, char** _out_src, size_t* _out_len = nullptr);
};
}	 // namespace dreco