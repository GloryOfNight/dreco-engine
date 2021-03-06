#pragma once
#include "resources/resource.hxx"

#include <stdint.h>

#include <string_view>

namespace dreco
{
class texture : public resource
{
public:
	texture(const char* _fpath);
	~texture();

	uint32_t GetTextureId() const;

private:
	uint32_t texture_id = 0;
};
}	 // namespace dreco