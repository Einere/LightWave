#pragma once

#include "Service.h"
#include "SocketWorker.h"
#include "Task.h"

namespace Service {
	/* �۾� �����Ϳ� ���� ó�� ��� */
	class TaskMonkey :
		public Service::Monkey
	{
	public:
		TaskMonkey();
		~TaskMonkey();

		/* ���� ���� �� �۾� ���� ��û*/
		virtual Json::Value DoGet(Json::Value props, Service::SocketWorker& socketWorker);

	protected:

		/*
		���޵� ��ü�� ���� json��ü�� ����
		���� ��ü�� �̹� ToJson�̶�� json��ȯ �Լ��� ���ǵǾ�������, �ʿ��� �ʵ常 ���������� ���� ����.
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