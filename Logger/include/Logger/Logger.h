#pragma once
#include <string_view>
#include <source_location>
#include <vector>
#include <memory>
#include <string>
#include <cassert>

#ifdef _WIN32
#define LOG(x, ...) LOGGER::Logger::GetInstance().Log(x, __VA_ARGS__)
#else
#define LOG(x, ...) LOGGER::Logger::GetInstance().Log(x, ##__VA_ARGS__)
#endif

#ifdef _WIN32
#define ERROR(x, ...) LOGGER::Logger::GetInstance().Error(std::source_location::current(), x, __VA_ARGS__)
#else
#define ERROR(x, ...) LOGGER::Logger::GetInstance().Error(std::source_location::current(), x, ##__VA_ARGS__)
#endif

#define ASSERT(x) assert(x);

#define LOG_CLEAR() LOGGER::Logger::GetInstance().ClearLogEntries();

#define LOG_INIT(consoleLog, retainLogs) LOGGER::Logger::GetInstance().Init(consoleLog, retainLogs);

namespace LOGGER
{

class Logger
{
  public:
	enum class LogType
	{
		INFO,
		WARN,
		ERR,
		NONE
	};
	struct LogEntry
	{
		LogType type;
		std::string message;
		LogEntry(LogType type = LogType::INFO, const std::string message = "")
			: type{type}
			, message{message}
		{
		}
	};

  private:
	std::string CurrentDateTime();
	std::vector<LogEntry> m_LogEntries{};
	bool m_bLogAdded{false}, m_bDestructed{false}, m_bConsoleLog{true}, m_bRetainLogs{true}, m_bInitialized{false};
	Logger() = default;

  public:
	static Logger& GetInstance();
	~Logger();
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

	void Init(bool consoleLog = true, bool retainLogs = true);

	template <typename... Args>
	void Log(const std::string_view message, Args... args);

	template <typename... Args>
	void Error(const std::source_location location, const std::string_view message, Args... args);

	inline const std::vector<LogEntry>& GetLogEntries() { return m_LogEntries; }
	void ClearLogEntries();
	inline void ResetLogAddition() { m_bLogAdded = false; }
	inline bool LogAdded() { return m_bLogAdded; }
};

} // namespace LOGGER

#include "Logger.inl"