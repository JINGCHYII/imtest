#pragma once

#include <functional>
#include <stdarg.h>

#define INFO(...) IO::Get().info(__VA_ARGS__)

class IO
{

public:
	static IO& Get() {
		static IO instance;
		return instance;
	}

	void info(const char* fmt, ...)
	{
		va_list args;
		va_start(args, fmt);
		vsnprintf(TempBuffer, 1024 * 3 + 1, fmt, args);
		va_end(args);
		log(0, TempBuffer);
	}


public:
	char TempBuffer[1024 * 3 + 1];
	std::function<void(int type, const char* msg)> log;

};
