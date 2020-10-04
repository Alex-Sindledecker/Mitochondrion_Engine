#pragma once

#include "Core.h"
#include "Debug/Debug.h"
#include "WindowInterface/Window.h"
#include "Rendering/Renderer.h"
#include "Core/ThreadPool.h"
#include "Core/StackAllocator.h"

#include "Layers/Layer.h"

namespace Engine
{

	class Application
	{
	public:
		static void init();
		static void terminate();

		static Window getWindow();
		static void run();
		static void pushLayer(const char* name, Layer* layer);
		static void setStaticTickRate(float ms);

		Application(const Application&) = delete;
		void operator=(const Application&) = delete;

	private:
		Application() {}
		~Application() {}

		static void loadDependencies();
		static void beginFrame();
		static void endFrame();
		static void handleEvents();
		static void runPhysics();

		static Window window;
		static ThreadPool asyncTaskManager;
		static StackAllocator singleFrameStack;
		static std::mutex physicsAccessMutex;
		static std::unordered_map<const char*, Layer*> layers;
		static Clock mainLoopClock;
	};

}