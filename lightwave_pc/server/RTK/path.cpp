#include "stdafx.h";
#include "path.h"

int Path::findLastSlash(CString path)
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

CString Path::getFileName(CString path)
{
	int lastSlashIndex = findLastSlash(path);
	assert(lastSlashIndex >= 0);

	return path.Right(path.GetLength() - lastSlashIndex - 1);
}

CString Path::getDirPath(CString path)
{
	int lastSlashIndex = findLastSlash(path);
	assert(lastSlashIndex >= 0);

	return path.Left(lastSlashIndex);
}
