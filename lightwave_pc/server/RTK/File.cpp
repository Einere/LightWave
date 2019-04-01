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
		/**************/


		/*bool isOpened = m_fileUtil.FileOpen(path, "w");
		if (!isOpened) return false;

		CString buf = toFileContent();
		bool isWritten = m_fileUtil.Write(buf);
		if (!isWritten) return false;

		bool isClosed=m_fileUtil.FileClose();
		assert(isClosed);
		
		return true;*/
	}

	bool Save::load(CString path)
	{
		return false;
	}

	CString Save::getDefaultPath()
	{
		return rootDir+"sample.tsk";
	}
}
