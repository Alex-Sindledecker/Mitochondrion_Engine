#pragma once

#include "Core.h"
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
	};

	App* createApp();

}

