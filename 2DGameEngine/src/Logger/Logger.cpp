#include <iomanip>
#include <iostream>
#include <format>

#include "Logger.h"

HANDLE Logger::hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
std::vector<LogEntry> Logger::messages{};

void Logger::Log(std::string_view message)
{
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);

	LogEntry log{ LogType::INFO };
	log.message = std::format("LOG: [ {} ]", getLocalTimeString());

	std::cout << log.message << "\n";
	messages.push_back(log);

	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
}

void Logger::Err(std::string_view message)
{
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);

	LogEntry log{ LogType::ERR };
	log.message = std::format("ERR: [ {} ]", getLocalTimeString());

	std::cerr << log.message << "\n";
	messages.push_back(log);

	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
}

std::string Logger::getLocalTimeString(void)
{
	constexpr int bufferSize{ 100 };
	char buffer[bufferSize];

	auto result{ std::time(nullptr) };
	std::tm localTime{};

	localtime_s(&localTime, &result);

	std::strftime(buffer, bufferSize, "%d/%m/%Y %H:%M:%S", static_cast<const std::tm*>(&localTime));

	return std::string(buffer);
}