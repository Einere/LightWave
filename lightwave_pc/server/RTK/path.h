#pragma once
#include "stdafx.h"

namespace Path {

	int findLastSlash(CString path);

	CString getFileName(CString path);

	CString getDirPath(CString path);
}