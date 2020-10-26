#pragma once

extern mito::Application* mito::createApp();

int main(int argc, char* argv[])
{
	mito::Application* app = mito::createApp();

	app->run();

	delete app;

	return 0;
}