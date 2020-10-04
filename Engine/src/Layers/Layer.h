#pragma once

#include "Core/Time.h"
#include "WindowInterface/Window.h"

namespace Engine
{

	class Application;

	class Layer
	{
	public:
		virtual ~Layer() = 0 {}

		virtual void onLoad() = 0;
		virtual void onFrameStart() = 0;
		virtual void onFrameEnd() = 0;
		virtual void onClose() = 0;

		friend class Application;

	protected:
		float deltaTime = 0.f;
		Window* window;
	};

}