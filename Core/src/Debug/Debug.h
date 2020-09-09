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

	class ENGINE_API EmptyLogTarget : public LogTarget
	{
	public:
		virtual const char* getName() override;
		virtual LogTarget* getHandle() override;
		virtual void logError(const char* msg, bool lf = true) override;
		virtual void logWarning(const char* msg, bool lf = true) override;
		virtual void logMessage(const char* msg, bool lf = true) override;
	} static EmptyLogger;

	class ENGINE_API DebugLogger
	{
	public:
		using LogLevel = int;
		const int LOG_ALL = 0b0111;
		const int LOG_ERROR = 0b0001;
		const int LOG_WARNING = 0b0010;
		const int LOG_MESSAGE = 0b0100;

	public:
		static DebugLogger& getInstance();

		void setTarget(LogTarget* handle);
		void setLevel(LogLevel level);

		template<class... Ts>
		void logError(std::string error, Ts... args)
		{
			if (mLogLevel & LOG_ERROR)
			{
				std::stringstream ss;
				ss << "[00:00:00](ERROR!)   -> ";
				logFormated(ss, error, 0, args...);
				mLogTarget->logError(ss.str().c_str());
			}
		}

		template<class... Ts>
		void logWarning(std::string warning, Ts... args)
		{
			if (mLogLevel & LOG_WARNING)
			{
				std::stringstream ss;
				ss << "[00:00:00](WARNING!) -> ";
				logFormated(ss, warning, 0, args...);
				mLogTarget->logWarning(ss.str().c_str());
			}
		}

		template<class... Ts>
		void logMessage(std::string message, Ts... args)
		{
			if (mLogLevel & LOG_MESSAGE)
			{
				std::stringstream ss;
				ss << "[00:00:00](MESSAGE)  -> ";
				logFormated(ss, message, 0, args...);
				mLogTarget->logMessage(ss.str().c_str());
			}
		}

		DebugLogger(const DebugLogger&) = delete;
		void operator=(const DebugLogger&) = delete;

	private:
		DebugLogger();
		~DebugLogger() {}

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