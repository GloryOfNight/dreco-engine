#include "shader_utils.hxx"

#include <fstream>
#include <iostream>
#include <sstream>

using namespace dreco;

std::string shader_utils::LoadShaderSource(const char* _fpath)
{
	std::fstream file(_fpath);

	if (!file.is_open())
	{
		std::cerr << "LoadShaderSource(): Failed to load file with location: " << _fpath << std::endl;
	}
	std::string line;
	std::stringstream src;

	while (getline(file, line))
	{
		src << line << '\n';
	}

	return src.str();
}