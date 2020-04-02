#pragma once
#include "resource.hxx"

#include <cstddef>

namespace dreco
{
class file_source : public resource
{
public:
	file_source(const char* _file_path);
	file_source(char* _file_source, const size_t& _size);
	~file_source();

	void GetSource(const char** _source, size_t* _size = nullptr) const;
	
private:
	char* source;
	size_t source_size;
};
}	 // namespace dreco