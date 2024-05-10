#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <format>
#include <chrono>

#include "Logger.h"

HANDLE Logger::hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
std::vector<LogEntry> Logger::messages{};

void Logger::Log(std::string_view message)
{
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);

	LogEntry log{ LogType::INFO };
	log.message = std::format("LOG: [ {} ] {}", getLocalTimeString(), message);

	std::cout << log.message << "\n";
	messages.push_back(log);

	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
}

void Logger::Err(std::string_view message)
{
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);

	LogEntry log{ LogType::ERR };
	log.message = std::format("ERR: [ {} ] {}", getLocalTimeString(), message);

	std::cerr << log.message << "\n";
	messages.push_back(log);

	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
}



std::string Logger::getLocalTimeString(void)
{
	char dstTime[100] = { 0 };
	const auto timeStamp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	std::strftime(dstTime, sizeof(dstTime), "%d/%m/%Y %H:%M:%S", std::localtime(&timeStamp));

	return std::string(dstTime);
}