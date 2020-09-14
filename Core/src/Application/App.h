#pragma once

#include "Core/Core.h"
#include "Debug/Debug.h"

namespace Engine
{

	class ENGINE_API App
	{
	public:
		App();
		virtual ~App();

		//Runs the application
		virtual void run();

	protected:
		DebugLogger& console;
	};

	App* createApp();

}

