#include "mepch.h"
#include "Application.h"

int main(int argc, char** argv)
{
	{
		EngineDebugger::beginProfilingSession("App");
		EngineDebugger::log("Engine startup...");

		Application app;

		DBG_PROFILE1(app.init);
		EngineDebugger::log("Startup complete! Running...");
		DBG_PROFILE1(app.run);
		DBG_PROFILE1(app.terminate);

		EngineDebugger::log("Engine shutdown...");

		auto appSession = EngineDebugger::endProfilingSession();
		EngineDebugger::printProfilingSession(appSession);
	}

	EngineDebugger::dumpMemoryLeaks();

	return 0;
}