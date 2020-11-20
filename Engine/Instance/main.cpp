#include "mepch.h"
#include "Application.h"

#include "Core/Debug/EngineDebugger.h"

int main(int argc, char** argv)
{
	EngineDebugger::log("Hello World!", EngineDebugger::LogType::ERR);
	EngineDebugger::log("Hello World?", EngineDebugger::LogType::WRN);
	EngineDebugger::log("Hello World");

	EngineDebugger::dumpMemoryLeaks();

	return 0;
}