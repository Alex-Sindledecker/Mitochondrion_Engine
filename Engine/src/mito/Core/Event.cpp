#include "mepch.h"
#include "Event.h"

#include "Application.h"

namespace mito
{
    std::queue<Event> EventManager::eventQueue;
    GLFWwindow* EventManager::windowPtr;

    void EventManager::init(GLFWwindow* windowPtr)
    {
        EventManager::windowPtr = windowPtr;

        glfwSetKeyCallback(windowPtr, keyCallback);
        glfwSetMouseButtonCallback(windowPtr, mouseButtonCallback);
        glfwSetScrollCallback(windowPtr, scrollCallback);
    }

    void EventManager::terminate()
    {
    }

    void EventManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        Event event;
        if (action == GLFW_PRESS)
            event.type = EventType::KeyPress;
        else if (action == GLFW_RELEASE)
            event.type = EventType::KeyRelease;
        event.key = static_cast<Key>(key);

        eventQueue.push(event);
    }

    void EventManager::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
    {
        Event event;
        if (action == GLFW_PRESS)
            event.type = EventType::MouseButtonPress;
        else if (action == GLFW_RELEASE)
            event.type = EventType::MouseButtonRelease;
        event.mouseButton = static_cast<MouseButton>(button);

        eventQueue.push(event);
    }

    void EventManager::scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
    {
        Event event;
        event.type = EventType::MouseScroll;
        event.mouseScroll.xOffset = xOffset;
        event.mouseScroll.yOffset = yOffset;

        eventQueue.push(event);
    }

    bool EventManager::pollEvent(Event* event)
    {
        if (eventQueue.size() == 0)
            return false;

        *event = eventQueue.front();
        eventQueue.pop();

        return true;
    }

    bool EventManager::isKeyPressed(Key key)
    {
        return glfwGetKey(windowPtr, (int)key);
    }

    bool EventManager::isKeyReleased(Key key)
    {
        return !glfwGetKey(windowPtr, (int)key);
    }

    bool EventManager::isMouseButtonPressed(MouseButton button)
    {
        return glfwGetMouseButton(windowPtr, (int)button);
    }

    bool EventManager::isMouseButtonReleased(MouseButton button)
    {
        return !glfwGetMouseButton(windowPtr, (int)button);
    }

    MousePos EventManager::getMousePos()
    {
        double x, y;
        glfwGetCursorPos(windowPtr, &x, &y);
        return { (float)x, (float)y };
    }

    void EventManager::_clearEventQueue()
    {
        eventQueue = {};
    }

}
