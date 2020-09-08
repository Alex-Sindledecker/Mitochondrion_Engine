#pragma once

#include "../Application/Core.h"
#include <sstream>
#include <iostream>

namespace Engine
{

	class ENGINE_API LogTarget
	{
	public:
		virtual ~LogTarget() = 0 {};

		virtual const char* getName() = 0;
		virtual LogTarget* getHandle() = 0;
		virtual void logError(const char* msg, bool lf = true) = 0;
		virtual void logWarning(const char* msg, bool lf = true) = 0;
		virtual void logMessage(const char* msg, bool lf = true) = 0;
	};

	class ENGINE_API Debug
	{
	public:
		using LogLevel = int;
		const int LOG_ALL = 0b0111;
		const int LOG_ERROR = 0b0001;
		const int LOG_WARN = 0b0010;
		const int LOG_MESSAGE = 0b0100;

	public:
		static Debug& getInstance();

		void setLogTarget(LogTarget* handle);
		void setLogLevel(LogLevel level);

		template<class... Ts>
		void logError(std::string error, Ts... args)
		{
			if (mLogLevel & LOG_ERROR)
			{
				std::stringstream ss("[00:00:00](ERROR!)   -> ");
				logFormated(ss, error, 0, args...);
				mLogTarget->logError(ss.str().c_str());
			}
		}

		template<class... Ts>
		void logWarning(std::string warning, Ts... args)
		{
			if (mLogLevel & LOG_WARN)
			{
				std::stringstream ss("[00:00:00](WARNING!) -> ");
				logFormated(ss, warning, 0, args...);
				mLogTarget->logWarning(ss.str().c_str());
			}
		}

		template<class... Ts>
		void logMessage(std::string message, Ts... args)
		{
			if (mLogLevel & LOG_MESSAGE)
			{
				std::stringstream ss("[00:00:00](MESSAGE)  -> ");
				logFormated(ss, message, 0, args...);
				mLogTarget->logMessage(ss.str().c_str());
			}
		}

		Debug(const Debug&) = delete;
		void operator=(const Debug&) = delete;

	private:
		Debug();
		~Debug() {}

		void logFormated(std::stringstream& ss, std::string& string, int offset) 
		{
			if (ss.str().length() == 0)
				ss << string;
			else
			{
				ss << string.substr(offset);
			}
		}

		template<class T, class... Ts>
		void logFormated(std::stringstream& ss, std::string& string, int offset, T arg, Ts... args)
		{
			auto start = string.find("{", offset);
			if (start != std::string::npos)
			{
				auto end = string.find("}", start);

				ss << string.substr(offset, start - offset) << arg;
				logFormated(ss, string, end + 1, args...);
			}
			else
			{
				ss << arg;
				logFormated(ss, string, offset, args...);
			}
		}

		LogTarget* mLogTarget;
		LogLevel mLogLevel;
	};

}