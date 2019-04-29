#include "stdafx.h"
#include "SurveyMonkey.h"

#include "Task.h"
#include "TaskManager.h"
#include "Base64Image.h"

#include "SurveyManager.h"


SurveyMonkey::SurveyMonkey() : Monkey("survey")
{
}


SurveyMonkey::~SurveyMonkey()
{
}

Json::Value SurveyMonkey::doPost(Json::Value props, SocketWorker& socketWorker)
{
	Json::Value jsonData = props["data"];

	UINT taskId = (jsonData["taskId"].isNull() ? -1 : jsonData["taskId"].asUInt());
	if (-1 == taskId) {
		return Service::error("\'taskId\' �ʵ尡 �������� ����.");
	}

	auto pTaskManager = ProgramManager::TaskManager::GetInstance();
	SurveyTask::Task* pTask;
	pTask = pTaskManager->getTaskById(taskId);
	if (pTask == NULL) {
		return Service::error("\'taskId\' �� �ش��ϴ� �۾��� �������� ����.");
	}

	UINT surveyId = (jsonData["surveyId"].isNull() ? -1 : jsonData["surveyId"].asUInt());
	SurveyTask::Survey survey;

	if (survey.HasBeenSurveyed()) {
		return Service::error("�ߺ� ��� �Ұ�: �Կ������� �̹� ��ϵ� ��ǥ�Դϴ�.");
	}

	Json::Value memoRoot = jsonData["memo"];
	if (memoRoot.isNull()) {
		return Service::error("\'memo\' �ʵ尡 �������� ����.");
	}

	survey.SetMemo(memoRoot.asCString());

	Json::Value imagesRoot = jsonData["images"];
	if (imagesRoot.isNull()) {
		return Service::error("\'images\' �ʵ尡 �������� ����.");
	}

	std::vector<CString> images;
	for (auto& img : imagesRoot) {
		images.push_back(img.asCString());
	}

	const int imagesCount = images.size();
	for (int i = 0; i < imagesCount; ++i) {
		SurveyTask::Base64Image b64img(pTask->GetParentPath(), images[i]);
		CString imgPath = b64img.store();
		survey.AppendImageFile(imgPath);
	}

	survey.setWorker(socketWorker.GetWorker());

	auto pSurvey = pTask->GetSurveyById(surveyId);
	pSurvey->Update(survey);

	pTask->store();

	auto onGoingTaskId = pTaskManager->getLoadedTask()->getId();
	if (taskId == onGoingTaskId) {
		ProgramManager::SurveyManager::GetInstance()->LoadSurveysFromTask(*pTask);
	}

	return Json::Value();
}
