#pragma once
#include <time.h>
#include <iomanip>
#include <cstdio>
#include <string>

class Date
{
public:
	static std::string getCurrentDate();
private:
	static std::time_t timer;
	static struct tm timeinfo;
};

