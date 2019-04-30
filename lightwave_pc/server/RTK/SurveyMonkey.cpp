#include "stdafx.h"
#include "SurveyMonkey.h"

#include "Task.h"
#include "TaskManager.h"
#include "Base64Image.h"

#include "SurveyViewManager.h"


SurveyMonkey::SurveyMonkey() : Monkey("survey")
{
}


SurveyMonkey::~SurveyMonkey()
{
}

Json::Value SurveyMonkey::DoPost(Json::Value props, SocketWorker& socketWorker)
{
	Json::Value jsonData = props["data"];

	UINT taskId = (jsonData["taskId"].isNull() ? -1 : jsonData["taskId"].asUInt());
	if (-1 == taskId) {
		return Service::Error("\'taskId\' 필드가 존재하지 않음.");
	}

	auto pTaskManager = ProgramManager::TaskManager::GetInstance();
	SurveyTask::Task* pTask;
	pTask = pTaskManager->GetTaskById(taskId);
	if (pTask == NULL) {
		return Service::Error("\'taskId\' 에 해당하는 작업이 존재하지 않음.");
	}

	UINT surveyId = (jsonData["surveyId"].isNull() ? -1 : jsonData["surveyId"].asUInt());
	SurveyTask::Survey survey;

	if (survey.HasBeenSurveyed()) {
		return Service::Error("중복 등록 불가: 촬영정보가 이미 등록된 좌표입니다.");
	}

	Json::Value memoRoot = jsonData["memo"];
	if (memoRoot.isNull()) {
		return Service::Error("\'memo\' 필드가 존재하지 않음.");
	}

	survey.SetMemo(memoRoot.asCString());

	Json::Value imagesRoot = jsonData["images"];
	if (imagesRoot.isNull()) {
		return Service::Error("\'images\' 필드가 존재하지 않음.");
	}

	std::vector<CString> images;
	for (auto& img : imagesRoot) {
		images.push_back(img.asCString());
	}

	const int imagesCount = images.size();
	for (int i = 0; i < imagesCount; ++i) {
		SurveyTask::Base64Image b64img(pTask->GetParentPath(), images[i]);
		CString imgPath = b64img.Store();
		survey.AppendImageFile(imgPath);
	}

	survey.setWorker(socketWorker.GetWorker());

	auto pSurvey = pTask->GetSurveyById(surveyId);
	pSurvey->Update(survey);

	pTask->Store();

	auto onGoingTaskId = pTaskManager->GetLoadedTask()->GetId();
	if (taskId == onGoingTaskId) {
		ProgramManager::SurveyViewManager::GetInstance()->LoadSurveysFromTask(*pTask);
	}

	return Json::Value();
}
