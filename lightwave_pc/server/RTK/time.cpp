#include "stdafx.h"
#include "time.h"

namespace TimeUtil {
	CString convertTime2Str(SYSTEMTIME t)
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
}