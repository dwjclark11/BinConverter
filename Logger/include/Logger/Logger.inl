#pragma once
#include "Logger.h"
#include <chrono>
#include <ctime>
#include <format>
#include <iostream>
#include <sstream>

#ifdef _WIN32
#include <Windows.h>
constexpr WORD GREEN = 2;
constexpr WORD RED = 4;
constexpr WORD YELLOW = 6;
constexpr WORD WHITE = 7;
#else
static const std::string GREEN = "\033[0;32m";
static const std::string YELLOW = "\033[0;33m";
static const std::string RED = "\033[0;31m";
static const std::string WHITE = "\033[0;30m";
static const std::string CLOSE = "\022[0m";
#endif

namespace LOGGER
{
template <typename... Args>
void Logger::Log(const std::string_view message, Args... args)
{
	assert(m_bInitialized && "The logger must be initialized before it is used!");

	if (!m_bInitialized)
	{
		std::cout << "The logger must be initialized before it is used!" << std::endl;
		return;
	}

	std::stringstream ss;
	ss << "LOG [INFO]: " << CurrentDateTime() << " - " << std::vformat(message, std::make_format_args(args...)) << "\n";

	if (m_bConsoleLog)
	{
#ifdef _WIN32
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, GREEN);
		std::cout << ss.str() << "\n";
		SetConsoleTextAttribute(hConsole, WHITE);
#else
		std::cout << GREEN << ss.str() << CLOSE << "\n";
#endif
	}

	if (m_bRetainLogs && !m_bDestructed)
	{
		m_LogEntries.emplace_back(LogType::INFO, ss.str());
		m_bLogAdded = true;
	}
}

template <typename... Args>
void Logger::Error(const std::source_location location, const std::string_view message, Args... args)
{
	assert(m_bInitialized && "The logger must be initialized before it is used!");

	if (!m_bInitialized)
	{
		std::cout << "The logger must be initialized before it is used!" << std::endl;
		return;
	}

	std::stringstream ss;
	ss << "LOG [ERROR]: " << CurrentDateTime() << " - " << std::vformat(message, std::make_format_args(args...))
	   << "\nFUNC: " << location.function_name() << "\nLINE: " << location.line() << "\n\n";

	if (m_bConsoleLog)
	{
#ifdef _WIN32
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, RED);
		std::cout << ss.str();
		SetConsoleTextAttribute(hConsole, WHITE);
#else
		std::cout << RED << ss.str() << CLOSE << "\n\n";
#endif
	}

	if (m_bRetainLogs && !m_bDestructed)
	{
		m_LogEntries.emplace_back(LogType::ERR, ss.str());
		m_bLogAdded = true;
	}
}
} // namespace LOGGER