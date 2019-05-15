#pragma once

#include "Service.h"
#include "SocketWorker.h"
#include "Task.h"

namespace Service {
	/* 작업 데이터에 대한 처리 담당 */
	class TaskMonkey :
		public Service::Monkey
	{
	public:
		TaskMonkey();
		~TaskMonkey();

		/* 현재 시작 된 작업 정보 요청*/
		virtual Json::Value DoGet(Json::Value props, Service::SocketWorker& socketWorker);

	protected:

		/*
		전달된 객체로 부터 json객체를 만듦
		많은 객체에 이미 ToJson이라는 json변환 함수가 정의되어있지만, 필요한 필드만 선별적으로 고르기 위함.
		*/
		Json::Value DeriveJsonFromTask(const SurveyTask::Task & task);
		Json::Value DeriveJsonFromSurveys(const std::vector<SurveyTask::Survey> & surveys);
		Json::Value DeriveJsonFromParcels(const std::vector<SurveyTask::ParcelToStore> & parcels);
		Json::Value DeriveJsonFromSurvey(const SurveyTask::Survey& survey);
		Json::Value DeriveJsonFromParcel(const SurveyTask::ParcelToStore& parcel);
		Json::Value DeriveJsonFromParcelPoints(const std::vector<SurveyTask::Point> & points);
		Json::Value DeriveJsonFromParcelPoint(const SurveyTask::Point & point);
	};
}