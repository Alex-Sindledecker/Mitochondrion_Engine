#include "pch.h"
#include "Rendering/Renderer.h"
#include "TestingLayer.h"

namespace Engine
{
	void TestingLayer::onLoad()
	{
		
	}

	void TestingLayer::onFrameStart()
	{
		OpenGLRenderer* renderer = dynamic_cast<OpenGLRenderer*>(Renderer::getRendererAPI());

		renderer->_renderTriangle();
	}

	void TestingLayer::onFrameEnd()
	{

	}

	void TestingLayer::onClose()
	{

	}
}