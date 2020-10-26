#include <Engine.h>

#include <iostream>

class SandboxApp : public mito::Application
{
public:

	void run() override { printf("Hello World!"); }

private:

};

//This is a test comment for git

mito::Application* mito::createApp()
{
	return new SandboxApp();
}