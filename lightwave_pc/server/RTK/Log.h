#pragma once

class CLogWnd;

class Log {
public:
	static CLogWnd lout;

	static CString getCurTime();

	static void log(const char* format, ...);

	static void err(const char* format, ...);

};
