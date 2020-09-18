#include "pch.h"
#include "FileLog.h"

#include "Debug/DebugTools.h"

namespace Engine
{

	FileLog::FileLog(std::string path, std::string name)
	{
		outPath = path;
		outName = name;
		outFile.open(outPath + outName, std::ios::app);
		ENGINE_ASSERT(outFile.is_open());
		outFile << "=============================\n" << "New Session Started\n" << "=============================\n";
	}

	FileLog::~FileLog()
	{
		outFile.close();
	}

	const std::string FileLog::getName() const
	{
		return outName;
	}

	const std::string FileLog::getPath() const
	{
		return outPath;
	}

	void FileLog::logError(const char* msg)
	{
		outFile << msg << '\n';
	}

	void FileLog::logWarning(const char* msg)
	{
		outFile << msg << '\n';
	}

	void FileLog::logMessage(const char* msg)
	{
		outFile << msg << '\n';
	}

}