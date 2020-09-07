#pragma once

#include "Core.h"

namespace Engine
{

	class ENGINE_API App
	{
	public:
		App();
		virtual ~App();

		void print(const char* str, int line = __LINE__, const char* file = __FILE__);

		//Runs the application
		virtual void run();
	};

	App* createApp();

}

