#include <mito/Engine.h>
#include <mito/Core/EntryPoint.h>

#include "ExampleLayer.h"

class SandboxApp : public mito::Application
{
public:

	void onProgramStart() override
	{
		createLayer<ExampleLayer>("MyLayer");
		attachLayer("MyLayer");
		detachLayer("MyLayer");
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