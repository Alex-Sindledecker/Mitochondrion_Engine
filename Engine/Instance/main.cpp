#include "mepch.h"
#include "Application.h"

#include "Core/Debug/EngineDebugger.h"
#include "Core/StringTools.h"

void wait(int seconds, bool istrue)
{
	std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

int main(int argc, char** argv)
{
	EngineDebugger::beginProfilingSession();

	EngineDebugger::beginProfile("printing");

	EngineDebugger::flog("DebugOutput.txt", "Hello World!", EngineDebugger::LogType::ERR);
	EngineDebugger::flog("DebugOutput.txt", "Hello World?", EngineDebugger::LogType::WRN);
	EngineDebugger::flog("DebugOutput.txt", "Hello World");

	EngineDebugger::endProfile();

	PROFILE(wait, 3, true);

	EngineDebugger::ProfilingSession session = EngineDebugger::endProfilingSession();
	EngineDebugger::printProfilingSession(session);

	EngineDebugger::dumpMemoryLeaks();

	return 0;
}