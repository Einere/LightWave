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

	// TODO: json ������ ��/�� validation �Լ��� ������ �����Ͽ� ȣ���ϱ�

	UINT taskId = (jsonData["taskId"].isNull() ? -1 : jsonData["taskId"].asUInt());
	if (-1 == taskId) {
		return Service::Error("\'taskId\' �ʵ尡 �������� ����.");
	}

	auto pTaskManager = ProgramManager::TaskManager::GetInstance();
	SurveyTask::Task* pTask;
	pTask = pTaskManager->GetTaskById(taskId);
	if (pTask == NULL) {
		return Service::Error("\'taskId\' �� �ش��ϴ� �۾��� �������� ����.");
	}

	UINT surveyId = (jsonData["surveyId"].isNull() ? -1 : jsonData["surveyId"].asUInt());
	auto pSurvey = pTask->GetSurveyById(surveyId);
	if (nullptr == pSurvey) {
		return Service::Error("��ȿ���� ���� ������ ���̵��Դϴ�.");
	}
	SurveyTask::Survey survey;

	if (survey.HasBeenSurveyed()) {
		return Service::Error("�ߺ� ��� �Ұ�: �Կ������� �̹� ��ϵ� ��ǥ�Դϴ�.");
	}

	Json::Value memoRoot = jsonData["memo"];
	if (memoRoot.isNull()) {
		return Service::Error("\'memo\' �ʵ尡 �������� ����.");
	}

	survey.SetMemo(memoRoot.asCString());

	Json::Value imagesRoot = jsonData["images"];
	if (imagesRoot.isNull()) {
		return Service::Error("\'images\' �ʵ尡 �������� ����.");
	}

	Json::Value geometriesRoot = jsonData["geometry"];
	if (geometriesRoot.isNull()) {
		return Service::Error("\'geometry\' �ʵ尡 �������� ����.");
	}

	int imageCount = imagesRoot.size();
	int geometryCount = geometriesRoot.size();
	if (imageCount != geometryCount) {
		return Service::Error("�̹����� ���浵���������� ������ ��ġ���� �ʽ��ϴ�.");
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
