#pragma once

#include "mito/Core/MitochondriaAPI.h"

#include <GLFW/glfw3.h>

#include <vector>
#include <queue>
#include <functional>

namespace mito
{

	enum class MITO_API EventType
	{
		WindowMove, WindowResize, WindowFocus, WindowLostFocus, WindowClose,
		KeyDown, KeyRelease, KeyPress, MouseButtonDown, MouseButtonRelease, MouseButtonPress,
		MouseScroll, MouseMove
	};

	enum class MITO_API Key : u16_t
	{
		//Common keys
		SPACE = 32, APOSTROPHE = 39, COMMA = 44, MINUS = 45, PERIOD = 46,
		SLASH = 47, NUM_ROW_0 = 48, NUM_ROW_1 = 49, NUM_ROW_2 = 50,
		NUM_ROW_3 = 51, NUM_ROW_4 = 52, NUM_ROW_5 = 53, NUM_ROW_6 = 54,
		NUM_ROW_7 = 55, NUM_ROW_8 = 56, NUM_ROW_9 = 57, SEMICOLON = 59,
		EQUAL = 61, A = 65, B = 66, C = 67, D = 68, E = 69, F = 70, G = 71,
		H = 72, I = 73, J = 74, K = 75, L = 76, M = 77, N = 78, O = 79,
		P = 80, Q = 81, R = 82, S = 83, T = 84, U = 85, V = 86, W = 87,
		X = 88, Y = 89, Z = 90, LEFT_BRACKET = 91, BACKSLASH = 92,
		RIGHT_BRACKET = 93, GRAVE_ACCENT = 96,

		//Function keys
		ESCAPE = 256, ENTER = 257, TAB = 258, BACKSPACE = 259,
		INSERT = 260, DEL = 261, RIGHT = 262, LEFT = 263, DOWN = 264,
		UP = 265, PAGE_UP = 266, PAGE_DOWN = 267, HOME = 268, END = 269,
		CAPS_LOCK = 280, SCROLL_LOCK = 281, NUM_LOCK = 282,
		PRINT_SCREEN = 283, PAUSE = 284, F1 = 290, F2 = 291, F3 = 292,
		F4 = 293, F5 = 294, F6 = 295, F7 = 296, F8 = 297, F9 = 298,
		F10 = 299, F11 = 300, F12 = 301, F13 = 302, F14 = 303,
		F15 = 304, F16 = 305, F17 = 306, F18 = 307, F19 = 308,
		F20 = 309, F21 = 310, F22 = 311, F23 = 312, F24 = 313,
		F25 = 314, NUM_PAD_0 = 320, NUM_PAD_1 = 321, NUM_PAD_2 = 322,
		NUM_PAD_3 = 323, NUM_PAD_4 = 324, NUM_PAD_5 = 325, NUM_PAD_6 = 326,
		NUM_PAD_7 = 327, NUM_PAD_8 = 328, NUM_PAD_9 = 329,
		NUM_PAD_DECIMAL = 330, NUM_PAD_DIVIDE = 331, NUM_PAD_MULTIPLY = 332,
		NUM_PAD_SUBTRACT = 333, NUM_PAD_ADD = 334, NUM_PAD_ENTER = 335,
		NUM_PAD_EQUAL = 336, LEFT_SHIFT = 340, LEFT_CONTROL = 341,
		LEFT_ALT = 342, LEFT_SUPER = 343, RIGHT_SHIFT = 344,
		RIGHT_CONTROL = 345, RIGHT_ALT = 346, RIGHT_SUPER = 347, MENU = 348,
	};

	enum class MITO_API MouseButton : u16_t
	{
		LEFT = 0, RIGHT, MIDDLE, BUTTON1, BUTTON2, BUTTON3, BUTTON4, BUTTON8
	};

	struct MousePos
	{
		float x, y;
	};

	struct MITO_API Event
	{
		EventType type;
		union
		{
			MousePos mousePos;
			struct
			{
				float xOffset, yOffset;
			} mouseScroll;
			struct
			{
				float x, y, width, height;
			} window;
			MouseButton mouseButton;
			Key key;
		};
	};

	class MITO_API Application;

	class MITO_API EventManager
	{
	public:
		static void init(GLFWwindow* windowPtr);
		static void terminate();

		static bool pollEvent(Event* event);
		static bool isKeyPressed(Key key);
		static bool isKeyReleased(Key key);
		static bool isMouseButtonPressed(MouseButton button);
		static bool isMouseButtonReleased(MouseButton button);
		static MousePos getMousePos();

		static void _clearEventQueue();

		EventManager(const EventManager&) = delete;
		void operator=(const EventManager&) = delete;

	private:
		static GLFWwindow* windowPtr;
		static std::queue<Event> eventQueue;
	private:
		EventManager() {}
		~EventManager() {}

		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
	};

}