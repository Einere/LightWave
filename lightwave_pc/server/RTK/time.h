#pragma once

#define INDEX_YEAR 0
#define INDEX_MONTH 1
#define INDEX_DAY 2
#define INDEX_DAYOFWEEK 3
#define INDEX_HOUR 4
#define INDEX_MINUTE 5
#define INDEX_SECOND 6
#define INDEX_MILLISECOND 7

namespace TimeUtil {
	CString ConvertTime2StrSimple(SYSTEMTIME t);
	CString ConvertTime2StrNumber(SYSTEMTIME t);
	SYSTEMTIME ConvertStrSimple2Time(CString s);
	CString ConvertTime2StrFormatted(SYSTEMTIME t);
}