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

	// TODO: json 데이터 유/무 validation 함수를 별도로 정의하여 호출하기

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
	auto pSurvey = pTask->GetSurveyById(surveyId);
	if (nullptr == pSurvey) {
		return Service::Error("유효하지 않은 측량점 아이디입니다.");
	}
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

	Json::Value geometriesRoot = jsonData["geometry"];
	if (geometriesRoot.isNull()) {
		return Service::Error("\'geometry\' 필드가 존재하지 않음.");
	}

	int imageCount = imagesRoot.size();
	int geometryCount = geometriesRoot.size();
	if (imageCount != geometryCount) {
		return Service::Error("이미지와 위경도방위정보의 갯수가 일치하지 않습니다.");
	}

	std::vector<CString> images;
	for (auto& img : imagesRoot) {
		images.push_back(img.asCString());
	}

	const int imagesCount = images.size();
	for (int i = 0; i < imagesCount; ++i) {
		SurveyTask::Base64Image b64img(pTask->GetParentPath(), images[i]);
		CString imgPath = b64img.Store();
		
		SurveyTask::Geometry geometry = {
			geometriesRoot[i]["latitude"].asDouble(),
			geometriesRoot[i]["longitude"].asDouble(),
			geometriesRoot[i]["azimuth"].asDouble()
		};

		survey.AppendImage({imgPath, geometry});
	}

	survey.setWorker(socketWorker.GetWorker());

	pSurvey->Update(survey);
	pTask->PatchSurvey(pSurvey->GetId(), *pSurvey);
	pTask->Store();

	auto pOnGoingTask = pTaskManager->GetLoadedTask();
	if (pOnGoingTask && taskId == pOnGoingTask->GetId()) {
		ProgramManager::SurveyViewManager::GetInstance()->LoadSurveysFromTask(*pTask);
	}

	return Json::Value();
}
