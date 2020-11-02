#include <mito/Engine.h>
#include <mito/Core/EntryPoint.h>

#include <mito-platform/OpenGL/ShaderProgram.h>

#include "ExampleLayer.h"

class SandboxApp : public mito::Application
{
public:

	void onProgramStart() override
	{
		createLayer<ExampleLayer>("MyLayer");
		attachLayer("MyLayer");
		detachLayer("MyLayer");

		mito::gl::ShaderProgram shader("../Engine/src/mito/Rendering/Shaders/tempVertex.glsl", 
										  "../Engine/src/mito/Rendering/Shaders/tempFragment.glsl");
	}

	void beginFrame() override
	{
		
	}

	void endFrame() override
	{
		
	}

private:

};

mito::Application* mito::createApp()
{
	return new SandboxApp();
}