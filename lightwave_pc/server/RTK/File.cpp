#include "stdafx.h"
#include "File.h"
#include "path.h"

using GlobalUtil::CFileUtil;
namespace fs = std::experimental::filesystem;

namespace File {
	Storable::Storable(CString parentDir)
	{
		m_parentPath = parentDir;
	}

	Storable::~Storable()
	{
	}

	CString Storable::Store(CString path)
	{
		if (!path || path == "") path = GetFilePath();
		m_filePath = CString(path);

		auto dirPath = Path::GetDirPath(path);
		if (GetFileAttributes(dirPath) == INVALID_FILE_ATTRIBUTES) {
			CreateDirectory(dirPath, NULL);
		}

		CFile file;
		const bool isOpenSucceed = file.Open(path, CFile::modeWrite | CFile::modeCreate);
		if (!isOpenSucceed) {
			return "";
		}

		auto buf = ToFileContent();

		file.Write((void*)buf.c_str(), buf.length());
		file.Close();

		return m_filePath;
	}

	bool Storable::Load(CString path)
	{
		CFile file;
		const bool isOpenSucceed = file.Open(path, CFile::modeRead);
		ASSERT(isOpenSucceed);

		int length = file.GetLength();
		char *buf = new char[length];
		file.Read((void*)buf, length);

		ASSERT(ResolveFileData(buf));

		file.Close();

		m_filePath = path;

		return true;
	}

	CString Storable::Remove(BOOL everything)
	{
		bool success = DeleteFile(m_filePath);
		if (!success) return "";

		auto dirPath = Path::GetDirPath(m_filePath);
		fs::directory_iterator itor((LPCTSTR)dirPath);
		UINT filesCount = 0;

		if (everything) {
			for (auto& file : itor) { 
				DeleteFileOrDirectory(file); 
			}
		}

		for (auto& file : itor) { ++filesCount; }

		if (0 == filesCount) {
			RemoveDirectory(dirPath);
		}

		return m_filePath;
	}

	bool Storable::CreateDir(CString path)
	{
		auto dirPath = Path::GetDirPath(path);
		if (GetFileAttributes(dirPath) == INVALID_FILE_ATTRIBUTES) {
			return CreateDirectory(dirPath, NULL);
		}
		else {
			return true;
		}
	}

	CString Storable::GetFilePath() const
	{
		CString filePath;
		filePath.Format("%s/%s.%s", m_parentPath, m_fileName, m_ext);
		return filePath;
	}

	CString Storable::GetFileName() const
	{
		return m_fileName;
	}

	CString Storable::GetExt() const
	{
		return m_ext;
	}

	CString Storable::GetParentPath() const
	{
		return m_parentPath;
	}

	void Storable::DeleteFileOrDirectory(fs::v1::directory_entry entry)
	{
		LPCWSTR path = entry.path().c_str();
		if (fs::is_directory(entry.status())) {
			fs::directory_iterator itor(entry);
			for (auto& entry : itor) { DeleteFileOrDirectory(entry); }
			RemoveDirectoryW(path);
		}
		else {
			DeleteFileW(path);
		}
	}

	void FindFile(const path & dirPath, const std::regex & regex, std::vector<path>& filesFound)
	{
		if (!exists(dirPath)) return;
		directory_iterator end_itr;
		for (directory_iterator itr(dirPath); itr != end_itr; ++itr) {
			if (is_directory(itr->status())) {
				FindFile(itr->path(), regex, filesFound);
			}
			else if (std::regex_match(itr->path().generic_string().c_str(), regex)) {
				filesFound.push_back(itr->path());
			}
		}
	}
}
