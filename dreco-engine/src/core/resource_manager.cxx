#include "resource_manager.hxx"

#include "core/engine.hxx"
#include "resources/audio.hxx"
#include "resources/file_source.hxx"
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

void resource_manager::LoadResource(const char* _fpath, resource_type _t)
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
				break;
			case resource_type::SOURCE_FILE:
				new_res = new file_source(_fpath);
				break;
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

void resource_manager::UnloadResource(const char* _fpath)
{
	if (IsResourceLoaded(_fpath))
	{
		resource* res = persistant_resources[_fpath];
		persistant_resources.erase(_fpath);

		delete res;
	}
}

resource* resource_manager::GetResource(const char* _fpath) const
{
	const bool is_loaded = IsResourceLoaded(_fpath);

	if (is_loaded)
	{
		return persistant_resources.at(_fpath);
	}

	return nullptr;
}

bool resource_manager::IsResourceLoaded(const char* _fpath) const
{
	return persistant_resources.find(_fpath) != persistant_resources.end();
}

void resource_manager::GetFileSource(const char* _fpath, const char** _source, size_t* _size) 
{
	const file_source* file_res = dynamic_cast<file_source*>(GetResource(_fpath));
	if (file_res && file_res->GetIsResourceLoaded()) 
	{
		file_res->GetSource(_source, _size);
	}
}