#include "pch.h"
#include "DebugConsole.h"

namespace Engine
{

	void DebugConsole::logError(const char* msg)
	{
		log(msg, FOREGROUND_RED);
	}

	void DebugConsole::logWarning(const char* msg)
	{
		log(msg, FOREGROUND_RED | FOREGROUND_GREEN);
	}

	void DebugConsole::logMessage(const char* msg)
	{
		log(msg, FOREGROUND_GREEN);
	}

	DebugConsole& DebugConsole::getInstance()
	{
		static DebugConsole instance;
		return instance;
	}

	void DebugConsole::log(const char* msg, u8_t color)
	{
		setTextColor(color);
		std::cout << msg << std::endl;
		setTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}

	void DebugConsole::setTextColor(int color)
	{
		static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, color);
	}

}