#pragma once

#include "GlobalUtil/FileUtil.h"
#include <regex>
#include <experimental/filesystem>

using namespace std::experimental::filesystem;

namespace File {

	const CString rootDir = "./working-data";
	const int MAX_PATH_LEN = 256;

	void FindFile(const path & dirPath, const std::regex & regex, std::vector<path>& filesFound);
	static DWORD CreateDir(CString path);
	static void handleDirCreationError(DWORD errorCode, CString dirPath = "");

	class Storable
	{
	public:
		Storable(CString parentPath = File::rootDir);
		~Storable();

		CString Store(CString path = NULL);
		bool Load(CString path);
		CString Remove(BOOL everything=FALSE);

		CString Storable::GetFilePath() const;
		CString GetFileName() const;
		CString GetExt() const;
		CString GetParentPath() const;
		CString GetCurrentPath() const;

		virtual std::string ToFileContent() = 0;

	protected:
		CString m_filePath;
		CString m_parentPath;
		CString m_fileName;
		CString m_ext;

		virtual BOOL ResolveFileData(const char* data) = 0;

	private:
		void DeleteFileOrDirectory(std::experimental::filesystem::v1::directory_entry entry);
		GlobalUtil::CFileUtil m_fileUtil;
	};
}

