#include "stdafx.h"
#include "OutputWnd.h"
#include "time.h"
#include "Log.h"

CLogWnd Logger::lout;

CString Logger::getTimestamp() {
	SYSTEMTIME curTime;
	GetLocalTime(&curTime);

	CString timestamp;
	timestamp.Format(_T("[%d-%d-%d %d:%d:%d.%d]"), 
		curTime.wYear, curTime.wMonth, curTime.wDay, 
		curTime.wHour, curTime.wMinute, curTime.wSecond, curTime.wMilliseconds);

	//std::time_t t = std::time(0);   // get time now
	//std::tm* now = std::localtime(&t);
	//CString nowStr;
	//nowStr.Format(_T("[%d-%d-%d %d:%d:%d.%d]"),
	//	now->tm_year + 1900, now->tm_mon + 1, now->tm_mday,
	//	now->tm_hour, now->tm_min, now->tm_sec, now->tm_
	//);

	return timestamp;
}


void Logger::Log(const char* format, ...) {
	CString content;
	va_list ap;

	std::string s;
	va_start(ap, format);

	content.FormatV(_T(format), ap);
	va_end(ap);

	lout.addLog("[notice]: " + getTimestamp() + "  " + content);
}

void Logger::Err(const char* format, ...) {
	CString msg;
	va_list ap;

	va_start(ap, format);
	msg.FormatV(_T(format), ap);
	va_end(ap);

	msg.Append(getTimestamp());

	lout.addLog("[error]: " + msg);
}