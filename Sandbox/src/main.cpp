#include <mito/Engine.h>
#include <mito/Debug/Debug.h>

#include <iostream>

class SandboxApp : public mito::Application
{
public:

	void run() override
	{
		
	}

private:

};

mito::Application* mito::createApp()
{
	return new SandboxApp();
}