#include "stdafx.h"
#include "TextEncoding.h"

namespace TextEncoding{
	std::string mulB2UTF8(std::string mbs)
	{
		USES_CONVERSION;

		return CW2A(CA2W(mbs.c_str()), CP_UTF8);
	}

	CString mulB2UTF8CString(CString mbs)
	{
		USES_CONVERSION;

		return CW2A(CA2W(mbs), CP_UTF8);
	}

	std::string UTF82mulB(std::string utfs)
	{
		USES_CONVERSION;

		return CW2A(CA2W(utfs.c_str(), CP_UTF8));
	}

	CString UTF82mulBCString(CString utfs)
	{
		USES_CONVERSION;

		return CW2A(CA2W(utfs, CP_UTF8));
	}
}