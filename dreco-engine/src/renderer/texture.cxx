#include "texture.hxx"

#ifdef __ANDROID__
#include "SDL_image.h"
#else
#include "SDL2/SDL_image.h"
#endif

#include "gl_check.hxx"
#include "gl_inline_functions.hxx"

using namespace dreco;

texture::texture(const std::string_view _path)
{
	SDL_Surface* res_texture = IMG_Load(_path.cbegin());

	if (!res_texture)
	{
		std::cerr << "GenerateTexture(): Invalid path: " << _path << std::endl;
		return;
	}

	glGenTextures(1, &texture_id);
	GL_CHECK();

	glBindTexture(GL_TEXTURE_2D, texture_id);
	GL_CHECK();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	GL_CHECK();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, res_texture->w, res_texture->h, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, res_texture->pixels);
	GL_CHECK();

	SDL_FreeSurface(res_texture);
}

texture::~texture()
{
	glDeleteTextures(1, &texture_id);
}

uint32_t texture::GetTextureId() const
{
	return texture_id;
}