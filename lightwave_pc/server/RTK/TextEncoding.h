#pragma once

namespace TextEncoding {
	std::string mulB2UTF8(std::string mbs);
	CString mulB2UTF8CString(CString mbs);
	std::string UTF82mulB(std::string utfs);
	CString UTF82mulBCString(CString utfs);
}