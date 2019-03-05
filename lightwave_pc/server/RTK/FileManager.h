#pragma once

class Task;

class FileManager
{
public:
	FileManager(LPCTSTR rootDir = "./working-data");
	~FileManager();

	static const int MAX_PATH_LEN = 256;

	bool saveTask(const Task& task);
	bool saveImage(LPCTSTR taskName, LPCTSTR img, LPCTSTR ext="jpeg");
	std::shared_ptr<Task> readTaskByName(LPCTSTR taskName);
	std::vector<std::shared_ptr<Task>> readTasksAll();
	//std::shared_ptr<Task> readByLotName(LPCTSTR lotName);

	int getFilePath(char result[MAX_PATH_LEN], LPCTSTR fileName, LPCTSTR ext);
	int getDirPath(char result[MAX_PATH_LEN], LPCTSTR dirName);
private:
	LPCTSTR m_rootDir;
};

