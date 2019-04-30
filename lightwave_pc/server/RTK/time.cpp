#include "stdafx.h"
#include "time.h"

namespace TimeUtil {
	CString ConvertTime2StrSimple(SYSTEMTIME t)
	{
		CString res;
		res.Format("%04d-%02d-%02d-%1d-%02d-%02d-%02d-%02d",
			t.wYear,
			t.wMonth,
			t.wDay,
			t.wDayOfWeek,
			t.wHour,
			t.wMinute,
			t.wSecond,
			t.wMilliseconds);
		return res;
	}

	CString ConvertTime2StrNumber(SYSTEMTIME t)
	{
		CString res;
		res.Format("%04d%02d%02d%1d%02d%02d%02d%02d",
			t.wYear,
			t.wMonth,
			t.wDay,
			t.wDayOfWeek,
			t.wHour,
			t.wMinute,
			t.wSecond,
			t.wMilliseconds);
		return res;
	}

	SYSTEMTIME ConvertStrSimple2Time(CString s)
	{
		const char* delimiter = "-";
		WORD tokens[8];
		CString token;
		int pos = 0;
		int index = 0;

		while ((token = s.Tokenize(delimiter, pos)) != "") {
			tokens[index] = atoi(token);
			++index;
		}
		assert(8 == index);

		SYSTEMTIME time;
		memcpy(&time, tokens, sizeof(WORD) * 8);
		return time;
	}

	CString ConvertTime2StrFormatted(SYSTEMTIME t)
	{
		CString res;
		res.Format("%d년 %d월 %d일 %d시 %d분 %d초",
			t.wYear,
			t.wMonth,
			t.wDay,
			t.wHour,
			t.wMinute,
			t.wSecond);
		return res;
	}
}