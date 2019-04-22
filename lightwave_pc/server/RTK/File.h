#pragma once

#include "GlobalUtil/FileUtil.h"
#include <regex>
#include <experimental/filesystem>

using namespace std::experimental::filesystem;

namespace File {

	const CString rootDir = "./working-data";
	const int MAX_PATH_LEN = 256;

	void findFile(const path & dirPath, const std::regex & regex, std::vector<path>& filesFound);

	class Storable
	{
	public:
		Storable(CString parentPath = File::rootDir);
		~Storable();

		CString store(CString path = NULL);
		bool load(CString path);
		CString remove(BOOL everything=FALSE);

		/*
		디렉토리가 이미 존재할 경우: true
		디렉토리 생성에 성공한 경우: true
		디렉토리 생성에 실패한 경우: false
		*/
		static bool CreateDir(CString path);

		CString Storable::GetFilePath() const;
		CString GetFileName() const;
		CString GetExt() const;
		CString GetParentPath() const;

		virtual std::string toFileContent() = 0;

	protected:
		CString m_filePath;
		CString m_parentPath;
		CString m_fileName;
		CString m_ext;

		virtual BOOL resolveFileData(const char* data) = 0;

	private:
		void deleteFileOrDirectory(std::experimental::filesystem::v1::directory_entry entry);
		GlobalUtil::CFileUtil m_fileUtil;
	};
}

