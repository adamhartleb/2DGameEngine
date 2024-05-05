#pragma once

#include <string>
#include <ctime>

class Logger 
{
public:
	static void Log(std::string_view message);
	static void Err(std::string_view message);
private:
	static std::string getLocalTimeString(void);
};