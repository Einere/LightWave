#include "stdafx.h"
#include "SurveyMonkey.h"

#include "Task.h"
#include "TaskManager.h"
#include "base64.h"


SurveyMonkey::SurveyMonkey() : Monkey("survey")
{
}


SurveyMonkey::~SurveyMonkey()
{
}

Json::Value SurveyMonkey::doPost(Json::Value props)
{
	Json::Value jsonData = props["data"];
	CString imgInStr = (jsonData["image"].isNull() ? "" : jsonData["image"].asCString());
	if (imgInStr.IsEmpty()) {
		return error("\'image\' �ʵ尡 �������� ����.");
	}

	UINT taskId = (jsonData["taskId"].isNull() ? -1 : jsonData["taskId"].asInt());
	if (-1 == taskId) {
		return error("\'taskId\' �ʵ尡 �������� ����.");
	}

	auto pTaskManager = ProgramManager::TaskManager::GetInstance();

	SurveyTask::Task task;
	BOOL exist = pTaskManager->getTaskById(taskId, task);
	if (!exist) {
		return error("\'taskId\' �� �ش��ϴ� �۾��� �������� ����.");
	}

	Log::log("�̹��� ������: %d", imgInStr.GetLength());
	auto decoded = base64_decode(imgInStr.GetString());
	const unsigned char* img = reinterpret_cast<const unsigned char*>(decoded.c_str());
	task.saveImage(img, decoded.length(), "test.jpg");

	return success("");
}
