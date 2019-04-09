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
		Storable();
		~Storable();

		bool store(CString path = NULL);
		bool load(CString path);
		bool remove(BOOL everything=FALSE);

		virtual CString toFileContent() = 0;

	protected:
		CString srcPath;

		virtual CString getDefaultPath();
		virtual BOOL resolveFileData(const char* data) = 0;

	private:
		void deleteFileOrDirectory(std::experimental::filesystem::v1::directory_entry entry);
		CString m_defaultPath;
		GlobalUtil::CFileUtil m_fileUtil;
	};
}
