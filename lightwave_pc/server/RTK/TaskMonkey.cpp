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
	if (pTask == NULL) return Service::error("���� ���� ���� �۾��� �������� �ʽ��ϴ�.");

	Json::Value root;
	root["data"] = pTask->toJson();

	return root;
}
