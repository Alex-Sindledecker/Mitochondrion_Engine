#include "pch.h"
#include "FileLog.h"

#include "Debug/DebugTools.h"

namespace Engine
{

	FileLog::FileLog(std::string path, std::string name)
	{
		mPath = path;
		mName = name;
		mOut.open(mPath + mName, std::ios::app);
		ENGINE_ASSERT(mOut.is_open());
		mOut << "=============================\n" << "New Session Started\n" << "=============================\n";
	}

	FileLog::~FileLog()
	{
		mOut.close();
	}

	const std::string FileLog::getName() const
	{
		return mName;
	}

	const std::string FileLog::getPath() const
	{
		return mPath;
	}

	void FileLog::logError(const char* msg)
	{
		mOut << msg << '\n';
	}

	void FileLog::logWarning(const char* msg)
	{
		mOut << msg << '\n';
	}

	void FileLog::logMessage(const char* msg)
	{
		mOut << msg << '\n';
	}

}