#pragma once

#include "Core/MitchondiraAPI.h"

namespace mito
{

	class MITO_API Application
	{
	public:

		virtual void run(){}

	private:

	};

	Application* createApp();

}