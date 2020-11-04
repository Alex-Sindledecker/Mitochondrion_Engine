#pragma once

extern mito::Application* mito::createApp();

int main(int argc, char* argv[])
{
	mito::Application* app = mito::createApp();

	//Init systems
	mito::Debug::init();
	app->init();
	mito::gl::init();
	mito::EventManager::init(app->getWindowPtr());

	//Run application
	app->run();

	//Destroy systems
	mito::EventManager::terminate();
	mito::gl::terminate();
	app->terminate();
	mito::Debug::terminate();

	delete app;

	return 0;
}