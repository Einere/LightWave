#include "stdafx.h";
#include "path.h"

int Path::FindLastSlash(CString path)
{
	int lastIndex = path.GetLength() - 1;
	for (int index = lastIndex; index >= 0; --index) {
		if (path[index] == '/' || path[index] == '\\') {
			return index;
			break;
		}
	}
	return -1;
}

CString Path::GetFileName(CString path)
{
	int lastSlashIndex = FindLastSlash(path);
	ASSERT(lastSlashIndex >= 0);

	return path.Right(path.GetLength() - lastSlashIndex - 1);
}

CString Path::GetDirPath(CString path)
{
	int lastSlashIndex = FindLastSlash(path);
	ASSERT(lastSlashIndex >= 0);

	return path.Left(lastSlashIndex);
}
