#include "stdafx.h"
#include "OutputWnd.h"
#include "Log.h"

CLogWnd Logger::lout;

CString Logger::getCurTime() {
	std::time_t t = std::time(0);   // get time now
	std::tm* now = std::localtime(&t);
	CString nowStr;
	nowStr.Format(_T("  [%d-%d-%d %d:%d:%d]"),
		now->tm_year + 1900, now->tm_mon + 1, now->tm_mday,
		now->tm_hour, now->tm_min, now->tm_sec
	);

	return nowStr;
}


void Logger::Log(const char* format, ...) {
	CString msg;
	va_list ap;

	std::string s;
	va_start(ap, format);
	
	msg.FormatV(_T(format), ap);
	va_end(ap);

	msg.Append(getCurTime());

	lout.addLog("[notice]: " + msg);
}

void Logger::Err(const char* format, ...) {
	CString msg;
	va_list ap;

	va_start(ap, format);
	msg.FormatV(_T(format), ap);
	va_end(ap);

	msg.Append(getCurTime());

	lout.addLog("[error]: " + msg);
}