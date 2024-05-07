#pragma once
#define WIN32_LEAN_AND_MEAN
#include <string>
#include <vector>
#include <Windows.h>

enum class LogType {
	DEBUG,
	INFO,
	WARNING,
	ERR
};

struct LogEntry {
	LogType type;
	std::string message;
};

class Logger 
{
public:
	static std::vector<LogEntry> messages;
	static void Log(std::string_view message);
	static void Err(std::string_view message);
private:
	static HANDLE hConsole;
	static std::string getLocalTimeString(void);
};