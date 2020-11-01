#include "ExampleLayer.h"

void ExampleLayer::onFrameStart()
{
}

void ExampleLayer::onFrameEnd()
{
}

void ExampleLayer::onEvent(mito::Event& event)
{
	
}

void ExampleLayer::onAttach()
{
	mito::Debug::log("Layer attached!");
}

void ExampleLayer::onDetach()
{
	mito::Debug::log("Layer detached!");
}
