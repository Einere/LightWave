#include "stdafx.h"
#include "TextEncoding.h"

namespace UTF8Encoding{
	std::string gogoUTF8(std::string mbs)
	{
		USES_CONVERSION;
		std::string strUTF8 = CW2A(CA2W(mbs.c_str()), CP_UTF8);

		return strUTF8;
	}
}