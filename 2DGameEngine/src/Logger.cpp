#include <iomanip>
#include <iostream>
#include <Windows.h>
#include "Logger.h"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void Logger::Log(std::string_view message)
{
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);

	std::cout << "[ " << getLocalTimeString() << " ] " << message << "\n";

	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
}

void Logger::Err(std::string_view message)
{
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);

	std::cerr << "[ " << getLocalTimeString() << " ] " << message << "\n";

	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
}

std::string Logger::getLocalTimeString(void)
{
	constexpr int bufferSize{ 100 };
	char buffer[bufferSize];

	auto result{ std::time(nullptr) };
	std::tm localTime{};

	localtime_s(&localTime, &result);

	const auto localTimeC = localTime;

	std::strftime(buffer, bufferSize, "%d/%m/%Y %H:%M:%S", &localTimeC);

	return std::string(buffer);
}