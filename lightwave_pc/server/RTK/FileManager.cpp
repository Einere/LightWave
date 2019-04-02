#include "stdafx.h"
//#include <iostream>
//#include <sstream>
//#include <string>
//
//#include "FileManager.h"
//#include "Task.h"
//
//FileManager::FileManager(LPCTSTR rootDir)
//{
//	m_rootDir = rootDir;
//
//	// 작업 디렉토리가 없으면 생성
//	if (GetFileAttributes(rootDir) == INVALID_FILE_ATTRIBUTES) {
//		CreateDirectory(rootDir, NULL);
//	}
//
//	/*Task t;
//	t["name"] = "First Job";
//	t["description"] = "Shit";
//	t["lotNumber"] = "12345";
//	t["fileName"] = "a.cif";
//
//	save(t);
//	auto pTask = readByTaskName("First Job");
//
//	for (Task::iterator itor = pTask->begin(); itor != pTask->end(); ++itor) {
//		MessageBox(NULL, itor->first, itor->second, MB_OK);
//	}*/
//}
//
//FileManager::~FileManager()
//{
//
//}
//
//bool FileManager::saveTask(const Task& task)
//{
//	char dirPath[MAX_PATH_LEN];
//	CString taskName = task.getTaskName();
//	sprintf_s(dirPath, "%s/%s", m_rootDir, taskName);
//	if (GetFileAttributes(dirPath) == INVALID_FILE_ATTRIBUTES) {
//		CreateDirectory(dirPath, NULL);
//	}
//
//	char filePath[MAX_PATH_LEN];
//	sprintf_s(filePath, "%s/%s.tsk", dirPath, taskName);
//	MessageBox(NULL, filePath, dirPath, MB_OK);
//	CFile file;
//	const bool isOpenSucceed = file.Open(filePath, CFile::modeWrite | CFile::modeCreate | CFile::modeNoTruncate);
//	assert(isOpenSucceed);
//
//	std::ostringstream os;
//	for (std::map<CString, CString>::const_iterator itor = task.begin(); itor != task.end(); ++itor) {
//		os << itor->first << ':' << itor->second << '\n';
//	}
//
//	std::string str = os.str();
//	str.at(str.length() - 1) = 0;
//	size_t bufLen = str.length();
//	file.Write((void*)str.c_str(), bufLen);
//	file.Close();
//
//	return true;
//}
//
//bool FileManager::saveImage(LPCTSTR taskName, LPCTSTR img, LPCTSTR ext)
//{
//
//	return false;
//}
//
//std::shared_ptr<Task> FileManager::readTaskByName(LPCTSTR taskName)
//{
//	CFile file;
//	
//	char filePath[MAX_PATH_LEN];
//	sprintf_s(filePath, "%s/%s/%s.tsk", m_rootDir, taskName, taskName);
//	const bool isOpenSucceed = file.Open(filePath, CFile::modeRead);
//	if (!isOpenSucceed) {
//		return nullptr;
//	}
//
//	ULONGLONG fileLength = file.GetLength();
//	char* buf = new char[fileLength];
//	file.Read((void*)buf, fileLength);
//
//	char *first = buf,
//		 *last = buf;
//
//	LPCTSTR key = nullptr,
//		    value = nullptr;
//	auto pTask = std::make_shared<Task>();
//
//	do {
//		if (':' == *last) {
//			*last = 0;
//			key = first;
//			assert(key);
//			first = last + 1;
//		}
//		else if ('\n' == *last || NULL == *last) {
//			*last = 0;
//			value = first;
//			assert(value);
//			first = last + 1;
//
//			(*pTask)[key] = value;
//
//			key = nullptr;
//			value = nullptr;
//		}
//
//		++last;
//	} while (last < &buf[fileLength]);
//
//	file.Close();
//
//	return pTask;
//}
//
//std::vector<std::shared_ptr<Task>> FileManager::readTasksAll()
//{
//		
//	return std::vector<std::shared_ptr<Task>>();
//}
//
//int FileManager::getFilePath(char result[MAX_PATH_LEN], LPCTSTR fileName, LPCTSTR ext)
//{
//	return 0;
//}
//
//int FileManager::getDirPath(char result[MAX_PATH_LEN], LPCTSTR dirName)
//{
//	return sprintf_s(result, MAX_PATH_LEN, "%s/%s", m_rootDir, dirName);
//}
//
