#include "stdafx.h"
#include "TaskMonkey.h"

#include "TaskManager.h"


TaskMonkey::TaskMonkey() : Monkey("task")
{
}


TaskMonkey::~TaskMonkey()
{
}

Json::Value TaskMonkey::doGet(Json::Value props, SocketWorker& socketWorker)
{
	auto pTaskManager = ProgramManager::TaskManager::GetInstance();

	SurveyTask::Task* pTask;
	pTask = pTaskManager->getStartedTask();
	if (pTask == NULL) return Service::error("현재 진행 중인 작업이 존재하지 않습니다.");

	Json::Value root;
	root["data"] = pTask->toJson();

	return root;
}
