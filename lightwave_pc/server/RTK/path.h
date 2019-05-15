#pragma once
#include "stdafx.h"

namespace Path {
	CString GetFileName(CString path);
	CString GetDirPath(CString path);

	int FindLastSlash(CString path);
}