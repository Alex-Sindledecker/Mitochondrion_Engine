#pragma once

#include <mito/Engine.h>

class ExampleLayer : public mito::Layer
{
public:
	virtual void onAttach() override;
	virtual void onDetach() override;
	virtual void onFrameStart() override;
	virtual void onFrameEnd() override;
	virtual void onEvent(mito::Event& event) override;
};

