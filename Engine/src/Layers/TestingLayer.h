#pragma once

#include "Layer.h"

namespace Engine
{

	class TestingLayer : public Layer
	{
	public:
		virtual void onFrameStart() override;
		virtual void onFrameEnd() override;
		virtual void onClose() override;
		virtual void onLoad() override;
	};

}
