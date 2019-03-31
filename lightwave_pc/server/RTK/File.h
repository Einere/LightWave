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

		//bool saveTask(const Task& task);
		//bool saveImage(LPCTSTR taskName, LPCTSTR img, LPCTSTR ext = "jpeg");
		//std::shared_ptr<Task> readTaskByName(LPCTSTR taskName);
		//std::vector<std::shared_ptr<Task>> readTasksAll();
		////std::shared_ptr<Task> readByLotName(LPCTSTR lotName);

		//int getFilePath(char result[MAX_PATH_LEN], LPCTSTR fileName, LPCTSTR ext);
		//int getDirPath(char result[MAX_PATH_LEN], LPCTSTR dirName);

	protected:
		virtual CString getDefaultPath();

	private:
		CString m_defaultPath;
		GlobalUtil::CFileUtil m_fileUtil;
	};
}

