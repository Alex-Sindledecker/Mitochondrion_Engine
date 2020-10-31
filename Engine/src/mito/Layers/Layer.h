#pragma once

#include "Core/MitchondiraAPI.h"
#include "Core/Event.h"

namespace mito
{

	class MITO_API Layer
	{
	public:
		virtual void onAttach() = 0;
		virtual void onDetach() = 0;
		virtual void onFrameStart() = 0;
		virtual void onFrameEnd() = 0;
		virtual void onEvent(Event& event) = 0;
	};

}