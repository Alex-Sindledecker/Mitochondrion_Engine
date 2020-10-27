#include "mepch.h"
#include "ConsoleLogger.h"

namespace mito
{

	void ConsoleLogger::logError(const char* msg)
	{
		log(msg, FOREGROUND_RED);
	}

	void ConsoleLogger::logWarning(const char* msg)
	{
		log(msg, FOREGROUND_RED | FOREGROUND_GREEN);
	}

	void ConsoleLogger::logMessage(const char* msg)
	{
		log(msg, FOREGROUND_GREEN);
	}

	ConsoleLogger& ConsoleLogger::getInstance()
	{
		static ConsoleLogger instance;
		return instance;
	}

	void ConsoleLogger::log(const char* msg, u8_t color)
	{
		setTextColor(color);
		std::cout << msg << std::endl;
		setTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}

	void ConsoleLogger::setTextColor(int color)
	{
		static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, color);
	}

}