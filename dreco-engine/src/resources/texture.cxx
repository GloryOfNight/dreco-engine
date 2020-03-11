#include "texture.hxx"

#ifdef __ANDROID__
#include "SDL_image.h"
#else
#include "SDL2/SDL_image.h"
#endif

#include "renderer/gl_check.hxx"
#include "renderer/gl_inline_functions.hxx"

using namespace dreco;

texture::texture(const char* _fpath) : resource(resource_type::TEXTURE)
{
	SDL_Surface* res_texture = IMG_Load(_fpath);

	if (!res_texture)
	{
		std::cerr << "texture(): Failed with Invalid path: " << IMG_GetError() << std::endl;
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

	is_resource_loaded = true;
}

texture::~texture()
{
	if (GetIsResourceLoaded())
	{
		glDeleteTextures(1, &texture_id);
	}
}

uint32_t texture::GetTextureId() const
{
	return texture_id;
}