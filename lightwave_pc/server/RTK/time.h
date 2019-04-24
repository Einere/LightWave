#pragma once

namespace TimeUtil {
	CString convertTime2StrSimple(SYSTEMTIME t);
	CString convertTime2StrNumber(SYSTEMTIME t);
	SYSTEMTIME convertStrSimple2Time(CString s);

	CString convertTime2StrFormatted(SYSTEMTIME t);
}