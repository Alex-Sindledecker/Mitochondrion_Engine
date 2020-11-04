#include <mito/Engine.h>
#include <mito/Core/EntryPoint.h>

#include "ExampleLayer.h"

const float vertices[] = {
	0.5f, 0.5f, 0.f,
	-0.5f, 0.5f, 0.f,
	-0.5f, -0.5f, 0.f,
	0.5f, -0.5f, 0.f
};

const GLuint indices[] = {
	0, 1, 2, 2, 3, 0 
};

class SandboxApp : public mito::Application
{
public:

	void onProgramStart() override
	{
		createLayer<ExampleLayer>("MyLayer");
		attachLayer("MyLayer");
		detachLayer("MyLayer");

		shader = mito::gl::ShaderProgram("res/shaders/tempVertex.glsl",
										  "res/shaders/tempFragment.glsl");
		mito::gl::VertexBuffer vbo = mito::gl::createStaticVertexBuffer(sizeof(vertices), vertices);
		mito::gl::ElementBuffer ebo = mito::gl::createStaticElementBuffer(sizeof(indices), indices);

		mito::gl::VertexAttribute att1;
		att1.vbo = vbo;
		att1.length = 3;
		att1.dataType = GL_FLOAT;
		att1.offset = (void*)0;
		att1.stride = 3 * sizeof(float);

		vao = mito::gl::createVertexArray(ebo, { att1 });

		mito::gl::deleteVertexBuffer(vbo);
		mito::gl::deleteElementBuffer(ebo);
	}

	void beginFrame() override
	{
		shader.bind();
 		mito::gl::_drawElements(vao, 6);
	}

	void endFrame() override
	{
		
	}

	void onProgramEnd() override
	{
		mito::gl::deleteVertexArray(vao);
	}

private:
	mito::gl::ShaderProgram shader;
	mito::gl::VertexArray vao;
};

mito::Application* mito::createApp()
{
	return new SandboxApp();
}