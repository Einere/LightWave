#include "stdafx.h"
#include "TextEncoding.h"

namespace UTF8Encoding{
	std::string W2UTF8(const std::wstring str)
	{
		std::string ret;
		int len = WideCharToMultiByte(CP_UTF8, 0, str.c_str(), str.length(), NULL, 0, NULL, NULL);
		if (len > 0)
		{
			ret.resize(len);
			WideCharToMultiByte(CP_UTF8, 0, str.c_str(), str.length(), &ret[0], len, NULL, NULL);
		}
		
		return ret;
	}
}