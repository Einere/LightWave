#include "stdafx.h"
#include "File.h"
#include "path.h"

using GlobalUtil::CFileUtil;

namespace File {
	Save::Save()
	{
	}

	Save::~Save()
	{
	}

	bool Save::save(CString path)
	{
		Log::log("%s", path);
		if (!path || path=="") path = getDefaultPath();

		auto dirPath = Path::getDirPath(path);
		if (GetFileAttributes(dirPath) == INVALID_FILE_ATTRIBUTES) {
			CreateDirectory(dirPath, NULL);
		}
		
		MessageBox(NULL, path, dirPath, MB_OK);
		CFile file;
		const bool isOpenSucceed = file.Open(path, CFile::modeWrite | CFile::modeCreate | CFile::modeNoTruncate);
		assert(isOpenSucceed);

		CString buf = toFileContent();

		file.Write((void*)buf.GetString(), buf.GetLength());
		file.Close();

		return true;
	}

	bool Save::load(CString path)
	{
		CFile file;
		const bool isOpenSucceed = file.Open(path, CFile::modeRead);
		assert(isOpenSucceed);

		int length = file.GetLength();
		char *buf = new char[length];
		file.Read((void*)buf, length);



		file.Close();

		return true;
	}

	CString Save::getDefaultPath()
	{
		return rootDir+"sample.tsk";
	}
}
