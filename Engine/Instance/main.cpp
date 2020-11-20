#include "mepch.h"
#include "Application.h"

int main(int argc, char** argv)
{
	{
		EngineDebugger::beginProfilingSession();

		Application app;

		PROFILE(app.init);
		PROFILE(app.run);
		PROFILE(app.terminate);

		auto appSession = EngineDebugger::endProfilingSession();
		EngineDebugger::printProfilingSession(appSession);
	}

	EngineDebugger::dumpMemoryLeaks();

	return 0;
}