#include "stdafx.h"
#include "File.h"
#include "path.h"

using GlobalUtil::CFileUtil;
namespace fs = std::experimental::filesystem;

namespace File {
	Storable::Storable()
	{
	}

	Storable::~Storable()
	{
	}

	bool Storable::store(CString path)
	{
		if (!path || path == "") path = getDefaultPath();
		srcPath = CString(path);

		auto dirPath = Path::getDirPath(path);
		if (GetFileAttributes(dirPath) == INVALID_FILE_ATTRIBUTES) {
			CreateDirectory(dirPath, NULL);
		}

		CFile file;
		const bool isOpenSucceed = file.Open(path, CFile::modeWrite | CFile::modeCreate);
		assert(isOpenSucceed);

		CString buf = toFileContent();

		file.Write((void*)buf.GetString(), buf.GetLength());
		file.Close();

		return true;
	}

	bool Storable::load(CString path)
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

	bool Storable::remove(BOOL everything)
	{
		bool success = DeleteFile(srcPath);

		auto dirPath = Path::getDirPath(srcPath);
		fs::directory_iterator itor((LPCTSTR)dirPath);
		UINT filesCount = 0;

		if (everything) {
			for (auto& file : itor) { deleteFileOrDirectory(file); }
		}

		for (auto& file : itor) { ++filesCount; }

		if (0 == filesCount) {
			RemoveDirectory(dirPath);
		}

		return success;
	}

	CString Storable::getDefaultPath()
	{
		return rootDir + "sample.tsk";
	}

	void Storable::deleteFileOrDirectory(fs::v1::directory_entry entry)
	{
		LPCWSTR path = entry.path().c_str();
		if (fs::is_directory(entry.status())) {
			RemoveDirectoryW(path);
		}
		else {
			DeleteFileW(path);
		}
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
