#include "stdafx.h"
#include "SurveyMonkey.h"

#include "Task.h"
#include "TaskManager.h"
#include "Base64Image.h"

#include "CadManager.h"


SurveyMonkey::SurveyMonkey() : Monkey("survey")
{
}


SurveyMonkey::~SurveyMonkey()
{
}

Json::Value SurveyMonkey::doPost(Json::Value props, SocketWorker& socketWorker)
{
	SurveyTask::Survey newSurvey;

	Json::Value jsonData = props["data"];

	UINT taskId = (jsonData["taskId"].isNull() ? -1 : jsonData["taskId"].asInt());
	if (-1 == taskId) {
		return Service::error("\'taskId\' �ʵ尡 �������� ����.");
	}

	auto pTaskManager = ProgramManager::TaskManager::GetInstance();
	SurveyTask::Task* pTask;
	pTask = pTaskManager->getTaskById(taskId);
	if (pTask == NULL) {
		return Service::error("\'taskId\' �� �ش��ϴ� �۾��� �������� ����.");
	}

	Json::Value jsonSurveyPoint = jsonData["surveyPoint"];
	if (jsonSurveyPoint.isNull() 
		|| jsonSurveyPoint["X"].isNull() 
		|| jsonSurveyPoint["Y"].isNull()) {
		return Service::error("\'surveyPoint\' �ʵ尡 �������� �ʰų� ������ �߸� ��.");
	}

	const double x = jsonSurveyPoint["X"].asDouble();
	const double y = jsonSurveyPoint["Y"].asDouble();

	auto pOldSurvey = pTask->GetSurveyByCoord(x, y);
	if (pOldSurvey) {
		return Service::error("�ߺ� ��� �Ұ�: �Կ������� �̹� ��ϵ� ��ǥ�Դϴ�.");
	}

	newSurvey.SetPoint(x, y);

	Json::Value memoRoot = jsonData["memo"];
	if (memoRoot.isNull()) {
		return Service::error("\'memo\' �ʵ尡 �������� ����.");
	}

	newSurvey.SetMemo(memoRoot.asCString());

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
		newSurvey.AppendImageFile(imgPath);
	}

	pTask->registerSurvey(newSurvey);
	pTask->store();

	auto onGoingTaskId = pTaskManager->getLoadedTask()->getId();
	if (taskId == onGoingTaskId) {
		ProgramManager::CCadManager::GetInstance()->ReCreateParcelData();
	}

	return Json::Value();
}
