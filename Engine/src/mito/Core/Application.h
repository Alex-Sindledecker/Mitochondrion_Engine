#pragma once

#include "mito/Core/MitochondriaAPI.h"
#include "mito/Core/Time.h"
#include "mito/Layers/Layer.h"

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

		void attachLayer(const char* name);
		void detachLayer(const char* name);
		void deleteLayer(const char* name);

		template<class T, typename = typename std::enable_if<std::is_base_of<Layer, T>::value>::type>
		void createLayer(const char* name)
		{
			layers[name] = std::shared_ptr<T>(new T);
		}

		virtual void onProgramStart();
		virtual void beginFrame();
		virtual void endFrame();
		virtual void onProgramEnd();

	protected:
		double deltaTime;

	private:
		void createWindow();

		GLFWwindow* window;
		Viewport windowViewport;
		Clock gameLoopClock;
		std::unordered_map<const char*, std::shared_ptr<Layer>> layers;
	};

	Application* createApp();

}