#include "file_source.hxx"

#include "resource_type.hxx"
#include "utils/file_utils.hxx"

using namespace dreco;

file_source::file_source(const char* _file_path) : resource(resource_type::SOURCE_FILE)
{
	file_utils::LoadSourceFromFile(_file_path, &source, &source_size);

	is_resource_loaded = nullptr != source;
}

file_source::file_source(char* _file_source, const size_t& _size)
	: resource(resource_type::SOURCE_FILE), source(_file_source), source_size(_size)
{
}

file_source::~file_source()
{
	if (is_resource_loaded)
	{
		delete[] source;
	}
}

void file_source::GetSource(const char** _source, size_t* _size) const
{
	if (*_source)
		*_source = source;
	if (_size)
		*_size = source_size;
}