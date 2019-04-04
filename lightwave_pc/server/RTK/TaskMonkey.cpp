#include "stdafx.h"
#include "TaskMonkey.h"

#include "TaskManager.h"


TaskMonkey::TaskMonkey() : Monkey("task")
{
}


TaskMonkey::~TaskMonkey()
{
}

Json::Value TaskMonkey::doGet(Json::Value props)
{
	auto pTaskManager = ProgramManager::TaskManager::GetInstance();

	SurveyTask::Task task;
	BOOL exist = pTaskManager->getStartedTask(task);
	if (!exist) return error("현재 진행 중인 작업이 존재하지 않습니다.");

	return task.toJson();
}
