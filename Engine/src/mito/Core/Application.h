#pragma once

#include "Core/MitchondiraAPI.h"
#include "Core/Time.h"
#include "Layers/Layer.h"

#include <GLFW/glfw3.h>
#include <vector>

namespace mito
{

	struct MITO_API Viewport
	{
		float x, y, width, height;
	};

	class MITO_API Application
	{
	public:
		void init();
		void terminate();
		void run();
		GLFWwindow* getWindowPtr();

		virtual void onProgramStart();
		virtual void beginFrame();
		virtual void endFrame();
		virtual void onProgramEnd();

		std::vector<Layer*> layers;

	protected:
		double deltaTime;

	private:
		void createWindow();

		GLFWwindow* window;
		Viewport windowViewport;
		Clock gameLoopClock;
		
	};

	Application* createApp();

}