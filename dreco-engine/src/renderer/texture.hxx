#pragma once
#include <string_view>

namespace dreco
{
class texture
{
public:
	texture(const std::string_view _path);
	~texture();

	uint32_t GetTextureId() const;

private:
	uint32_t texture_id = 0;
};
}	// namespace dreco