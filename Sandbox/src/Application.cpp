#include <Engine.h>
#include <Debug/Debug.h>
#include <Debug/Logging/FileLog.h>

#include <Application/Window.h>
#include <Core/StackAllocator.h>

#include <iostream>

int temp = 0;

class Application : public Engine::App
{
public:
	void run() override
	{
		Engine::Window window(1280, 720, "Hello Engine!");

		while (!window.isCloseRequested())
		{
			for (Engine::Event event : window.pollEvents())
			{
				if (event.type == Engine::EventType::KEY_PRESS && event.key.code == Engine::Key::SPACE)
					Logger.logMessage("Mouse position: {}, {}", Engine::getMousePos().x, Engine::getMousePos().y);
			}
			if (Engine::isKeyPressed(Engine::Key::RIGHT))
				Logger.logMessage("Right arrow key pressed!");


			window.swapBuffers();
		}
	}
};

Engine::App* Engine::createApp()
{
	return new Application();
}