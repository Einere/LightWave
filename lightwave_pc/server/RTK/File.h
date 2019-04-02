#pragma once

#include "GlobalUtil/FileUtil.h"

namespace File {

	const CString rootDir = "./working-data";
	const int MAX_PATH_LEN = 256;

	class Save
	{
	public:
		Save();
		~Save();

		bool save(CString path = NULL);
		bool load(CString path);

		virtual CString toFileContent() = 0;

	protected:
		virtual CString getDefaultPath();
		virtual BOOL resolveFileData(const char* data)=0;

	private:
		CString m_defaultPath;
		GlobalUtil::CFileUtil m_fileUtil;
	};
}

