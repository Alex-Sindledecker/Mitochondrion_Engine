#pragma once

#include "Core.h"
#include "Debug/Debug.h"

namespace Engine
{

	class ENGINE_API App
	{
	public:
		DebugLogger& Debug;
	public:
		App();
		virtual ~App();

		//Runs the application
		virtual void run();

	private:
		
	};

	App* createApp();

}

