#pragma once

#include <glad/glad.h>

namespace gl
{

	GLenum getChannelEnum(int channels);

	class Texture
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