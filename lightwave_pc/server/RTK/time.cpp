#include "stdafx.h"
#include "time.h"

namespace TimeUtil {
	CString convertTime2StrSimple(SYSTEMTIME t)
	{
		CString res;
		res.Format("%04d%02d%02d%02d%02d%02d",
			t.wYear,
			t.wMonth,
			t.wDay,
			t.wHour,
			t.wMinute,
			t.wSecond);
		return res;
	}
	CString convertTime2StrFormatted(SYSTEMTIME t)
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