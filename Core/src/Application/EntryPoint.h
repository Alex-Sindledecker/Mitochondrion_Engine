#pragma once

extern Engine::App* Engine::createApp();

int main(int argc, char** argv)
{
	Engine::App* app = Engine::createApp();

	app->run();

	delete app;
}