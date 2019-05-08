#include "stdafx.h"
#include "TaskMonkey.h"
#include "TaskManager.h"
#include "CoordConverter.h"


TaskMonkey::TaskMonkey() : Monkey("task")
{
}


TaskMonkey::~TaskMonkey()
{
}

Json::Value TaskMonkey::DoGet(Json::Value props, SocketWorker& socketWorker)
{
	auto pTaskManager = ProgramManager::TaskManager::GetInstance();

	SurveyTask::Task* pTask;
	pTask = pTaskManager->GetStartedTask();
	if (pTask == NULL) return Service::Error("현재 진행 중인 작업이 존재하지 않습니다.");

	Json::Value root;
	root["data"] = DeriveJsonFromTask(*pTask);

	return root;
}

Json::Value TaskMonkey::DeriveJsonFromTask(const SurveyTask::Task & task)
{
	Json::Value root;
	root["id"] = task.GetId();
	root["taskName"] = task.GetTaskName().GetString();
	root["taskDesc"] = task.GetTaskDesc().GetString();
	root["landNo"] = task.GetLotNumber().GetString();
	root["parcels"] = DeriveJsonFromParcels(task.GetParcels());	
	root["surveyPoints"] = DeriveJsonFromSurveys(task.GetSurveys());
	
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
	double x = const_cast<SurveyTask::Survey*>(&survey)->GetX();
	double y = const_cast<SurveyTask::Survey*>(&survey)->GetY();
	CoordConverter::TMtoWGS84(&x, &y);
	root["X"] = x;
	root["Y"] = y;
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
	double x = point.first;
	double y = point.second;
	CoordConverter::TMtoWGS84(&x, &y);
	root["X"] = x;
	root["Y"] = y;

	return root;
}
