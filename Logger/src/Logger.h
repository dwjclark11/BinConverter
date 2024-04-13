#pragma once
#include <string_view>
#include <source_location>
#include <vector>
#include <memory>
#include <string>
#include <cassert>

#ifdef _WIN32
#include <Windows.h>
constexpr WORD BLACK = 0;
constexpr WORD BLUE = 1;
constexpr WORD GREEN = 2;
constexpr WORD AQUA = 3;
constexpr WORD RED = 4;
constexpr WORD PURPLE = 5;
constexpr WORD YELLOW = 6;
constexpr WORD WHITE = 7;
constexpr WORD GRAY = 8;
constexpr WORD LIGHT_BLUE = 9;
constexpr WORD LIGHT_GREEN = 10;
constexpr WORD LIGHT_AQUA = 11;
constexpr WORD LIGHT_RED = 12;
constexpr WORD LIGHT_PURPLE = 13;
constexpr WORD LIGHT_YELLOW = 14;
constexpr WORD BRIGHT_WHITE = 15;
#endif


#define LOG(x, ...)		LOGGER::Logger::GetInstance().Log(x, __VA_ARGS__);
#define ERROR(x, ...)	LOGGER::Logger::GetInstance().Error(std::source_location::current(), x, __VA_ARGS__);
#define ASSERT(x)		assert(x);

#define LOG_CLEAR()		LOGGER::Logger::GetInstance().ClearLogEntries();

#define LOG_INIT(consoleLog, retainLogs)	LOGGER::Logger::GetInstance().Init(consoleLog, retainLogs);

namespace LOGGER {

	class Logger
	{
	public:
		enum class LogType { INFO, WARN, ERR, NONE };
		struct LogEntry
		{
			LogType type;
			std::string message;
			LogEntry(LogType type = LogType::INFO, const std::string message = "")
				: type{ type }, message{ message }
			{}
		};

	private:
		std::string CurrentDateTime();
		std::vector<LogEntry> m_LogEntries{};
		bool m_bLogAdded{ false }, m_bDestructed{ false }, m_bConsoleLog{ true }, m_bRetainLogs{ true }, m_bInitialized{ false };
		Logger() = default;
	
	public:
		static Logger& GetInstance();
		~Logger();
		Logger(const Logger&) = delete;
		Logger& operator=(const Logger&) = delete;

		void Init(bool consoleLog = true, bool retainLogs = true);

		template <typename ...Args>
		void Log(const std::string_view& message, Args... args);

		template <typename ...Args>
		void Error(const std::source_location location, const std::string_view& message, Args... args);

		inline const std::vector<LogEntry>& GetLogEntries() { return m_LogEntries; }
		void ClearLogEntries();
		inline void ResetLogAddition() { m_bLogAdded = false; }
		inline bool LogAdded() { return m_bLogAdded; }
	};

}

#include "Logger.inl"