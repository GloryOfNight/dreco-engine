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

	void LoadResource(std::string _fpath, resource_type _t);

	void UnloadResource(std::string _fpath);

	// can return nullptr when resource with _fpath was not found
	resource* GetResource(const std::string _fpath) const;

	bool IsResourceLoaded(const std::string _fpath) const;

private:
	engine* owner;

	// resources that alive when manager alive
	std::map<std::string, resource*> persistant_resources = {};
};
}	 // namespace dreco