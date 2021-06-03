#include "pch.h"
#include "Date.h"

std::time_t Date::timer;
struct tm Date::timeinfo;

std::string Date::getCurrentDate()
{
	time(&timer);
	localtime_s(&timeinfo, &timer);
	std::string month, day, hour, minute;
	if (timeinfo.tm_mon + 1 < 10)
		month = "0" + std::to_string(timeinfo.tm_mon + 1);
	else
		month = std::to_string(timeinfo.tm_mon + 1);

	if (timeinfo.tm_mday + 1 < 10)
		day = "0" + std::to_string(timeinfo.tm_mday);
	else
		day = std::to_string(timeinfo.tm_mday);

	if (timeinfo.tm_hour < 10)
		hour = "0" + std::to_string(timeinfo.tm_hour);
	else
		hour = std::to_string(timeinfo.tm_hour);

	if (timeinfo.tm_min < 10)
		minute = "0" + std::to_string(timeinfo.tm_min);
	else
		minute = std::to_string(timeinfo.tm_min);

	return std::to_string(1900 + timeinfo.tm_year) + "." + month + "." + day + "-" + hour + ":" + minute;
}
