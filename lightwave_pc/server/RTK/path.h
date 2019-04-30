#pragma once
#include "stdafx.h"

namespace Path {

	int FindLastSlash(CString path);

	CString GetFileName(CString path);

	CString GetDirPath(CString path);
}