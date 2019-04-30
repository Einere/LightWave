#pragma once

namespace TimeUtil {
	CString ConvertTime2StrSimple(SYSTEMTIME t);
	CString ConvertTime2StrNumber(SYSTEMTIME t);
	SYSTEMTIME ConvertStrSimple2Time(CString s);

	CString ConvertTime2StrFormatted(SYSTEMTIME t);
}