#pragma once
//
//#include <iostream>
//#include <mutex>
//
//#include "OutputWnd.h"
//class CLogWnd;
//
//
//namespace Log {
//	extern CLogWnd lout;
//	//void init(CLogWnd*);
//	void log(const char* format, ...);
//	void err(const char* format, ...);
//}

//
//void myAssert(bool condition, const char* msg) {
//	std::cerr << "Assertion failed at " << __FILE__ << ":" << __LINE__;
//	std::cerr << " inside " << __FUNCTION__ << std::endl;
//	std::cerr << "["<< msg <<"]";
//	abort();
//}



class Common
{
public:
	Common();
	~Common();

	static const wchar_t* GetWC(const char *c)
	{
		size_t length = strlen(c) + 1;
		wchar_t wc[50];
		mbstowcs_s(&length, wc, c, length);

		LPCTSTR s = "abc";

		return wc;
	}
};

