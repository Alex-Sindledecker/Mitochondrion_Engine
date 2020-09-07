#include <iostream>
#include <Engine.h>
#include <Application/EntryPoint.h>
#include <Debug/DebugConsole.h>

class Application : public Engine::App
{
public:
	void run() override
	{
		//Ideas for what a logger might look like
		//Debug::LogError("Buffer memory overflow!"); ----> "[00:00:00](ERROR!) -> Buffer memory overflow!"
		//Debug::LogWarning("Buffer memory limit reached! Consider allocating more memory."); ----> "[00:00:12](WARNING!) -> Buffer memory limit reached! Consider allocating more memory..."
		//Debug::LogMessage("Allocated 1024 bytes at {}", hex(ptr)); ----> "[00:00:24](MESSAGE) -> Allocated 1024 bytes at 0xFEAB012C"
		//Debug::SetLogLevel(Debug::LogLevel::ALL) ----> Show messages, warnings, and errors
		//Debug::SetLogLevel(Debug::LogLevel::WARN) ----> Show warnings, and errors
		//Debug::SetLogLevel(Debug::LogLevel::ERROR) ----> Show errors
		//Debug::SetLogLevel(Debug::LogLevel::ERROR | Debug::LogLevel::MESSAGE) ----> Show errors and messages
		//Debug::SetLogTarget(DebugConsole.GetHandle()) ----> All logs will fed into the windows console
		//Debug::SetLogTarget(ImGUICosnole.GetHandle()) ----> All logs will fed into the imgui console
		//Debug::SetLogTarget(OutFile.GetHandle()) ----> All logs will be fed into an output file
		//DEBUG_FILE_LINE_STR ----> "File: C:\temp\[REDACTED] Game Engine\Sandbox\src\Application.cpp, Line: 20"
		//Warnings print yellow, errors print red, messages print green

		Engine::DebugConsole& console = Engine::DebugConsole::getInstance();
		console.logError("This is my error text!");
		console.logWarning("This is my warning text!");
		console.logMessage("This is my message text!");
	}


};

Engine::App* Engine::createApp()
{
	return new Application();
}