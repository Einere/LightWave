#pragma once

#include "Service.h"
#include "SocketWorker.h"

namespace Service {
	/* �������� ��û�� ��� */
	class SurveyMonkey :
		public Service::Monkey
	{
	public:
		SurveyMonkey();
		~SurveyMonkey();

		/* ����, �޸� �� ��� ó�� */
		virtual Json::Value DoPost(Json::Value props, SocketWorker& socketWorker);
	};
}