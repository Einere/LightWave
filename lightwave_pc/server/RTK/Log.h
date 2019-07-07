#pragma once

class CLogWnd;

class Logger {
public:
	static CLogWnd lout;

	static CString getTimestamp();

	static void Log(const char* format, ...);

	static void Err(const char* format, ...);

};
