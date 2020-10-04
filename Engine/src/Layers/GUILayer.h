#pragma once

#include "Layer.h"

namespace Engine
{

	class GUILayer : public Layer
	{
	public:
		virtual void onLoad() override;
		virtual void onFrameStart() override;
		virtual void onFrameEnd() override;
		virtual void onClose() override;

	private:
		void buildGUI();
	};

}