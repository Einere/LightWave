#include "stdafx.h"
#include "ParcelMonkey.h"

#include "TaskManager.h"

ParcelMonkey::ParcelMonkey() : Monkey("parcel")
{

}

ParcelMonkey::~ParcelMonkey()
{
}

Json::Value ParcelMonkey::DoGet(Json::Value props, SocketWorker& socketWorker)
{
	auto pTaskManager = ProgramManager::TaskManager::GetInstance();
	auto tasks = pTaskManager->GetTasks();

	Json::Value jsonTasksList(Json::arrayValue);
	for (auto& task : tasks) {
		Json::Value jsonTask;
		jsonTask["taskId"] = task.GetId();
		jsonTask["taskName"] = (LPCTSTR)task.GetTaskName();
		jsonTask["taskDesc"] = (LPCTSTR)task.GetTaskDesc();
		jsonTasksList.append(jsonTask);
	}

	Json::Value jsonData;
	jsonData["count"] = tasks.size();
	jsonData["items"] = jsonTasksList;

	Json::Value root;
	root["data"] = jsonData;
	
	return root;
}