#pragma once

#include "Service.h"
#include "SocketWorker.h"

namespace Service {
	/* 측량점에 요청을 담당 */
	class SurveyMonkey :
		public Service::Monkey
	{
	public:
		SurveyMonkey();
		~SurveyMonkey();

		/* 사진, 메모 등 등록 처리 */
		virtual Json::Value DoPost(Json::Value props, SocketWorker& socketWorker);
	};
}