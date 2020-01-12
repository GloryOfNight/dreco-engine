#include "resource_manager.hxx"

#include "core/engine.hxx"
#include "resources/audio.hxx"
#include "resources/music.hxx"
#include "resources/resource.hxx"
#include "resources/texture.hxx"

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
				new_res = new texture(_fpath);
				break;
			case resource_type::AUDIO:
				new_res = new audio(_fpath);
				break;
			case resource_type::MUSIC:
				new_res = new music(_fpath);
		}

		if (new_res)
		{
			if (new_res->GetIsResourceLoaded())
			{
				persistant_resources.emplace(_fpath, new_res);
			}
			else
			{
				delete new_res;
			}
		}
	}
}

void resource_manager::UnloadResource(std::string _fpath)
{
	if (IsResourceLoaded(_fpath))
	{
		resource* res = persistant_resources[_fpath];
		persistant_resources.erase(_fpath);

		delete res;
	}
}

resource* resource_manager::GetResource(const std::string _fpath) const
{
	const bool is_loaded = IsResourceLoaded(_fpath);

	if (is_loaded)
	{
		return persistant_resources.at(_fpath);
	}

	return nullptr;
}

bool resource_manager::IsResourceLoaded(const std::string _fpath) const
{
	return persistant_resources.find(_fpath) != persistant_resources.end();
}
