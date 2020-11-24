#include "mepch.h"
#include "Texture.h"

#include "Core/Utilities.h"

namespace gl
{

	GLenum getChannelEnum(int channels)
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
		util::Image image = util::loadImage(src);

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

		util::freeImage(&image);
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