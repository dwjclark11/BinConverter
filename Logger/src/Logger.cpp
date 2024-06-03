#define _CRT_SECURE_NO_WARNINGS

#include <Logger/Logger.h>
#include <chrono>
#include <ctime>
#include <iostream>

namespace LOGGER
{

std::string Logger::CurrentDateTime()
{
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	char output[ 30 ];
	std::strftime(&output[ 0 ], 30, "%y-%m-%d %H:%M:%S", std::localtime(&now));

	return std::string{output};
}

Logger::~Logger()
{
	std::cout << "Logger Destroyed!\n";
	// Hack -- Logger is being destroyed too early
	m_bDestructed = true;
}

Logger& Logger::GetInstance()
{
	static Logger instance{};
	return instance;
}

void Logger::Init(bool consoleLog, bool retainLogs)
{
	assert(!m_bInitialized && "Do not call Initialize more that once!");
	if (m_bInitialized)
	{
		std::cout << "Logger has already been intialized!" << std::endl;
		return;
	}

	m_bConsoleLog = consoleLog;
	m_bRetainLogs = retainLogs;
	m_bInitialized = true;
}

void Logger::ClearLogEntries()
{
	m_LogEntries.clear();
}
} // namespace LOGGER
