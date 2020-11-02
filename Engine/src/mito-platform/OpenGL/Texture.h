#pragma once

#include "mito/Core/MitochondriaAPI.h"

#include <glad/glad.h>

namespace mito::gl
{

	struct Image
	{
		int width;
		int height;
		int channels;
		unsigned char* pixels;
	};

	bool MITO_API loadImage(const char* src, Image* image);
	void MITO_API freeImage(Image* image);
	GLenum MITO_API getChannelEnum(int channels);

	class MITO_API Texture
	{
	public:
		virtual ~Texture() = 0 {}
		
		virtual void bind() = 0;
		virtual void unbind() = 0;

	protected:
		GLuint id;
	};

	class Texture2D : public Texture
	{
	public:
		Texture2D(const char* src);
		~Texture2D();

		virtual void bind() override;
		virtual void unbind() override;
	};

}