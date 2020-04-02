#pragma once
#include <stdint.h>

namespace dreco
{
struct gl_shader_info
{
	gl_shader_info(
		const char* _vertex_path, const char* _fragment_path, const char* _binary_path)
		: vertex_shader_path{_vertex_path}
		, fragment_shader_path{_fragment_path}
		, program_binary_path{_binary_path}
		, program_binary_source{nullptr}
		, program_binary_size{0}
	{
	}

	gl_shader_info(const char* _binary_path, char* _binary_source, const size_t& _size)
		: vertex_shader_path{nullptr}
		, fragment_shader_path{nullptr}
		, program_binary_path{_binary_path}
		, program_binary_source{_binary_source}
		, program_binary_size{_size}
	{
	}
	~gl_shader_info()
	{
		if (HasBinary())
		{
			delete[] program_binary_source;
		}
	}

	bool HasBinary() const
	{
		return 0 < program_binary_size && nullptr != program_binary_source;
	}

	void GetBinary(const char** _bin, size_t* _size)
	{
		if (*_bin)
			*_bin = program_binary_source;
		if (_size)
			*_size = program_binary_size;
	}

	const char* vertex_shader_path;
	const char* fragment_shader_path;
	const char* program_binary_path;

private:
	char* program_binary_source;
	const size_t program_binary_size;
};
}	 // namespace dreco