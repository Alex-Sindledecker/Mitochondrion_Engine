#include "mepch.h"
#include "Texture.h"
#include "mito/Debug/Debug.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stbimage.h>

namespace mito::gl
{

	bool MITO_API loadImage(const char* src, Image* image)
	{
		image->pixels = stbi_load(src, &image->width, &image->height, &image->channels, 0);
		if (image->pixels == nullptr)
			return false;
		return true;
	}

	void MITO_API freeImage(Image* image)
	{
		stbi_image_free(image->pixels);
	}

	GLenum MITO_API getChannelEnum(int channels)
	{
		switch (channels)
		{
		case 1:
			return GL_RED;
		case 2:
			return GL_RG;
		case 3:
			return GL_RGB;
		case 4:
			return GL_RGBA;
		default:
			return GL_RED;
		}
	}

	Texture2D::Texture2D(const char* src)
	{
		Image image;
		if (!loadImage(src, &image))
		{
			Debug::log(Debug::WRN_LOG, "Failed to load image: \"{}\"!", src);
			return;
		}

		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, getChannelEnum(image.channels), image.width, image.height,
			         0, GL_RGB, GL_UNSIGNED_INT, image.pixels);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		freeImage(&image);
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &id);
	}

	void Texture2D::bind()
	{
		glBindTexture(GL_TEXTURE_2D, id);
	}

	void Texture2D::unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}