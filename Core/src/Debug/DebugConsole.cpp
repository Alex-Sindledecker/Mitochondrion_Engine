#include "DebugConsole.h"

#include <iostream>
#include <Windows.h>

namespace Engine
{

	const char* DebugConsole::getName()
	{
		return "Windows Console";
	}

	LogTarget* DebugConsole::getHandle()
	{
		return this;
	}

	void DebugConsole::logError(const char* msg)
	{
		setTextColor(FOREGROUND_RED);
		log(msg);
	}

	void DebugConsole::logWarning(const char* msg)
	{
		setTextColor(FOREGROUND_RED | FOREGROUND_GREEN);
		log(msg);
	}

	void DebugConsole::logMessage(const char* msg)
	{
		setTextColor(FOREGROUND_GREEN);
		log(msg);
	}

	DebugConsole& DebugConsole::getInstance()
	{
		static DebugConsole instance;
		return instance;
	}

	void DebugConsole::log(const char* msg)
	{
		std::cout << msg << std::endl;
		setTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}

	void DebugConsole::setTextColor(int color)
	{
		static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, color);
	}

}