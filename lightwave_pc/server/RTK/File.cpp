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
		if (!path || path == "") path = getDefaultPath();
		srcPath = CString(path);

		auto dirPath = Path::getDirPath(path);
		if (GetFileAttributes(dirPath) == INVALID_FILE_ATTRIBUTES) {
			CreateDirectory(dirPath, NULL);
		}

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

		assert(resolveFileData(buf));

		file.Close();

		srcPath = path;

		return true;
	}

	bool Save::remove()
	{
		bool success = DeleteFile(srcPath);

		auto dirPath = Path::getDirPath(srcPath);
		std::experimental::filesystem::directory_iterator itor((LPCTSTR)dirPath);
		UINT filesCount = 0;
		for (auto& file : itor) { ++filesCount; }
		if (0 == filesCount) {
			RemoveDirectory(dirPath);
		}

		return success;
	}

	CString Save::getDefaultPath()
	{
		return rootDir + "sample.tsk";
	}
	void findFile(const path & dirPath, const std::regex & regex, std::vector<path>& filesFound)
	{
		if (!exists(dirPath)) return;
		directory_iterator end_itr;
		for (directory_iterator itr(dirPath); itr != end_itr; ++itr) {
			if (is_directory(itr->status())) {
				findFile(itr->path(), regex, filesFound);
			}
			else if (std::regex_match(itr->path().generic_string().c_str(), regex)) {
				filesFound.push_back(itr->path());
			}
		}
	}
}
