#include <mito/Engine.h>
#include <mito/Core/Event.h>

#include <iostream>

class TestLayer : public mito::Layer
{
public:
	virtual void onFrameStart() override
	{
	}
	virtual void onFrameEnd() override
	{
	}
	virtual void onEvent(mito::Event& event) override
	{
		mito::Debug::log(mito::Debug::MSG_LOG, "Event occurred!");
		/*
		if (mito::isKeyPressed(mito::Key::RIGHT))
			mito::Debug::log(mito::Debug::MSG_LOG, "Right arrow key pressed!");
		*/
	}
};

class SandboxApp : public mito::Application
{
public:

	void onProgramStart() override
	{
		layers.push_back(new TestLayer);
	}

	void beginFrame() override
	{
		mito::Event event;
		while (mito::EventManager::pollEvent(&event))
		{
			if (event.type == mito::EventType::KeyPress)
				if (event.key == mito::Key::SPACE)
					std::cout << "Space button pressed!" << std::endl;
		}
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