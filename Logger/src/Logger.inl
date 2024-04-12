#pragma once
#include "Logger.h"
#include <format>
#include <Windows.h>
#include <iostream>
#include <sstream>
#include <cassert>

namespace LOGGER {
	template <typename ...Args>
	void Logger::Log(const std::string_view& message, Args... args)
	{
		assert(m_bInitialized && "The logger must be initialized before it is used!");

		if (!m_bInitialized)
		{
			std::cout << "The logger must be initialized before it is used!" << std::endl;
			return;
		}

		std::stringstream ss;
		ss << "LOG [INFO]: " << CurrentDateTime() << " - " << std::vformat(message, std::make_format_args(std::forward<Args>(args)...)) << "\n";

		if (m_bConsoleLog)
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, GREEN);
			std::cout << ss.str();
			SetConsoleTextAttribute(hConsole, WHITE);
		}

		if (m_bRetainLogs && !m_bDestructed)
		{
			m_LogEntries.emplace_back(LogType::INFO, ss.str());
			m_bLogAdded = true;
		}
	}

	template <typename ...Args>
	void Logger::Error(const std::source_location location, const std::string_view & message, Args... args)
	{
		assert(m_bInitialized && "The logger must be initialized before it is used!");

		if (!m_bInitialized)
		{
			std::cout << "The logger must be initialized before it is used!" << std::endl;
			return;
		}

		std::stringstream ss;
		ss << "LOG [ERROR]: " << CurrentDateTime() << " - " << std::vformat(message, std::make_format_args(std::forward<Args>(args)...)) <<
			"\nFUNC: " << location.function_name() <<
			"\nLINE: " << location.line() << "\n\n";

		if (m_bConsoleLog)
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, RED);
			std::cout << ss.str();
			SetConsoleTextAttribute(hConsole, WHITE);
		}

		if (m_bRetainLogs && !m_bDestructed)
		{
			m_LogEntries.emplace_back(LogType::ERR, ss.str());
			m_bLogAdded = true;
		}
	}
}