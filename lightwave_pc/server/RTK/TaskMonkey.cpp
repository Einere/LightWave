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
	if (pTask == NULL) return Service::error("현재 진행 중인 작업이 존재하지 않습니다.");

	Json::Value root;
	root["data"] = DeriveJsonFromTask(*pTask);

	return root;
}

Json::Value TaskMonkey::DeriveJsonFromTask(const SurveyTask::Task & task)
{
	Json::Value root;
	root["id"] = task.getId();
	root["taskName"] = task.getTaskName().GetString();
	root["taskDesc"] = task.getTaskDesc().GetString();
	root["landNo"] = task.getLotNumber().GetString();
	root["parcels"] = DeriveJsonFromParcels(task.getParcels());	
	root["surveyPoints"] = DeriveJsonFromSurveys(task.getSurveys());
	
	return root;
}

Json::Value TaskMonkey::DeriveJsonFromSurveys(const std::vector<SurveyTask::Survey>& surveys)
{
	Json::Value root = Json::Value(Json::arrayValue);
	for (auto& survey : surveys) {
		root.append(DeriveJsonFromSurvey(survey));
	}

	return root;
}

Json::Value TaskMonkey::DeriveJsonFromParcels(const std::vector<SurveyTask::ParcelToStore>& parcels)
{
	Json::Value root = Json::Value(Json::arrayValue);
	for (auto& parcel : parcels) {
		root.append(DeriveJsonFromParcel(parcel));
	}

	return root;
}

Json::Value TaskMonkey::DeriveJsonFromSurvey(const SurveyTask::Survey & survey)
{
	Json::Value root;
	root["id"] = survey.GetId();
	root["X"] = const_cast<SurveyTask::Survey*>(&survey)->GetX();
	root["Y"] = const_cast<SurveyTask::Survey*>(&survey)->GetX();
	root["surveyed"] = survey.HasBeenSurveyed();

	return root;
}

Json::Value TaskMonkey::DeriveJsonFromParcel(const SurveyTask::ParcelToStore & parcel)
{
	Json::Value root;
	root["landNo"] = parcel.landNo.GetString();
	root["parcelPoints"] = DeriveJsonFromParcelPoints(parcel.points);

	return root;
}

Json::Value TaskMonkey::DeriveJsonFromParcelPoints(const std::vector<SurveyTask::Point>& points)
{
	Json::Value root = Json::Value(Json::arrayValue);
	for (auto& pt : points) {
		root.append(DeriveJsonFromParcelPoint(pt));
	}

	return root;
}

Json::Value TaskMonkey::DeriveJsonFromParcelPoint(const SurveyTask::Point & point)
{
	Json::Value root;
	root["X"] = point.first;
	root["Y"] = point.second;

	return root;
}
