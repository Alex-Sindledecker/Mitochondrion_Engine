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

	void DebugConsole::logError(const char* msg, bool lf)
	{
		setTextColor(FOREGROUND_RED);
		log(msg, lf);
	}

	void DebugConsole::logWarning(const char* msg, bool lf)
	{
		setTextColor(FOREGROUND_RED | FOREGROUND_GREEN);
		log(msg, lf);
	}

	void DebugConsole::logMessage(const char* msg, bool lf)
	{
		setTextColor(FOREGROUND_GREEN);
		log(msg, lf);
	}

	DebugConsole& DebugConsole::getInstance()
	{
		static DebugConsole instance;
		return instance;
	}

	void DebugConsole::log(const char* msg, bool lf)
	{

		std::cout << msg;
		if (lf)
			std::cout << '\n';
		setTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}

	void DebugConsole::setTextColor(int color)
	{
		static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, color);
	}

}