#pragma once

extern Engine::App* Engine::createApp();

int main(int argc, char** argv)
{
	Engine::App* app = Engine::createApp();
	
	//Init core systems
	Engine::Debug::init();

	app->run();

	delete app;
}