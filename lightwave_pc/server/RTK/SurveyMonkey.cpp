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

Json::Value SurveyMonkey::doPost(Json::Value props)
{
	Json::Value jsonData = props["data"];
	Json::Value jsonSurveyPoint = jsonData["surveyPoint"];
	if (jsonSurveyPoint.isNull() 
		|| jsonSurveyPoint["X"].isNull() 
		|| jsonSurveyPoint["Y"].isNull()) {
		return Service::error("\'surveyPoint\' 필드가 존재하지 않거나 형식이 잘못 됨.");
	}

	Json::Value imagesRoot = jsonData["images"];
	if (imagesRoot.isNull()) {
		return Service::error("\'images\' 필드가 존재하지 않음.");
	}

	Json::Value memoRoot = jsonData["memo"];
	if (memoRoot.isNull()) {
		return Service::error("\'memo\' 필드가 존재하지 않음.");
	}

	UINT taskId = (jsonData["taskId"].isNull() ? -1 : jsonData["taskId"].asInt());
	if (-1 == taskId) {
		return Service::error("\'taskId\' 필드가 존재하지 않음.");
	}

	auto pTaskManager = ProgramManager::TaskManager::GetInstance();
	SurveyTask::Task* pTask;
	pTask = pTaskManager->getTaskById(taskId);
	if (pTask == NULL) {
		return Service::error("\'taskId\' 에 해당하는 작업이 존재하지 않음.");
	}

	CString memo = memoRoot.asCString();

	std::vector<CString> images;
	for (auto& img : imagesRoot) {
		images.push_back(img.asCString());
	}
	
	const double x = jsonSurveyPoint["X"].asDouble();
	const double y = jsonSurveyPoint["Y"].asDouble();

	auto pOldSurvey = pTask->GetSurveyByCoord(x, y);
	if (pOldSurvey) {
		return Service::error("중복 등록 불가: 촬영정보가 이미 등록된 좌표입니다.");
	}

	SurveyTask::Survey newSurvey;

	newSurvey.SetPoint(x, y);
	newSurvey.SetMemo(memo);

	const int imagesCount = images.size();
	for (int i = 0; i < imagesCount; ++i) {
		SurveyTask::Base64Image b64img(pTask->GetParentPath(), images[i]);
		CString imgPath = b64img.store();
		newSurvey.AppendImageFile(imgPath);
	}

	pTask->registerSurvey(newSurvey);
	pTask->store();

	ProgramManager::CCadManager::GetInstance()->ReCreateParcelData();

	return Json::Value();
}
