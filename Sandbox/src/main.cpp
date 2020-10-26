#include <Engine.h>

#include <iostream>

class SandboxApp : public mito::Application
{
public:

	void run() override { printf("Hello World!"); }

private:

};

mito::Application* mito::createApp()
{
	return new SandboxApp();
}