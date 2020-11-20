#include "mepch.h"
#include "EventController.h"

void EventController::pollEvents()
{
	glfwPollEvents();
}
