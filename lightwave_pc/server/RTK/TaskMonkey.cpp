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
	if (!exist) return error("���� ���� ���� �۾��� �������� �ʽ��ϴ�.");

	return task.toJson();
}
