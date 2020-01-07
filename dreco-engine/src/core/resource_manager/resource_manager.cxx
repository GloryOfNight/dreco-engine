#include "resource_manager.hxx"

#include "core/engine.hxx"
#include "renderer/texture.hxx"
#include "resource.hxx"

using namespace dreco;

resource_manager::resource_manager(engine& _e) : owner(&_e)
{
}

resource_manager::~resource_manager()
{
	for (auto res : persistant_resources)
	{
		delete res.second;
	}
}

void resource_manager::LoadResource(std::string _fpath, resource_type _t)
{
	if (!IsResourceLoaded(_fpath))
	{
		resource* new_res = nullptr;

		switch (_t)
		{
			case resource_type::TEXTURE:
				new_res = dynamic_cast<resource*>(new texture(_fpath));
				break;
		}

		if (new_res)
		{
			persistant_resources.emplace(_fpath, new_res);
		}
	}
}

resource* resource_manager::GetResource(const std::string _fpath)
{
	bool is_loaded = IsResourceLoaded(_fpath);

	if (is_loaded)
	{
		return persistant_resources[_fpath];
	}

	return nullptr;
}

bool resource_manager::IsResourceLoaded(const std::string _fpath)
{
	return persistant_resources.find(_fpath) != persistant_resources.end();
}
