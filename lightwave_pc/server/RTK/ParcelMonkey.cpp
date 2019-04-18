#include "stdafx.h"
#include "ParcelMonkey.h"

#include "TaskManager.h"

ParcelMonkey::ParcelMonkey() : Monkey("parcel")
{

}

ParcelMonkey::~ParcelMonkey()
{
}

Json::Value ParcelMonkey::doGet(Json::Value props)
{
	auto pTaskManager = ProgramManager::TaskManager::GetInstance();
	auto tasks = pTaskManager->getTasks();

	Json::Value jsonTasksList(Json::arrayValue);
	for (auto& task : tasks) {
		Json::Value jsonTask;
		jsonTask["taskId"] = task.getId();
		jsonTask["taskName"] = (LPCTSTR)task.getTaskName();
		jsonTask["taskDesc"] = (LPCTSTR)task.getTaskDesc();
		jsonTasksList.append(jsonTask);
	}

	Json::Value jsonData;
	jsonData["count"] = tasks.size();
	jsonData["items"] = jsonTasksList;

	Json::Value root;
	root["data"] = jsonData;
	
	return root;
}