#pragma once
#include "resources/resource_type.hxx"

#include <map>
#include <string>

namespace dreco
{
class engine;

class resource;

class resource_manager
{
public:
	resource_manager(engine& _e);
	~resource_manager();

	void LoadResource(const char* _fpath, resource_type _t);

	void UnloadResource(const char* _fpath);

	// can return nullptr when resource with _fpath was not found
	resource* GetResource(const char* _fpath) const;

	bool IsResourceLoaded(const char* _fpath) const;

	void GetFileSource(const char* _fpath, const char** _source, size_t* _size);
	
private:
	engine* owner;

	// resources that alive when manager alive
	std::map<std::string, resource*> persistant_resources = {};
};
}	 // namespace dreco