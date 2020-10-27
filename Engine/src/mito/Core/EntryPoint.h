#pragma once

extern mito::Application* mito::createApp();

int main(int argc, char* argv[])
{
	//Init systems
	mito::Debug::init();

	mito::Application* app = mito::createApp();

	app->run();

	delete app;

	mito::Debug::terminate();

	return 0;
}