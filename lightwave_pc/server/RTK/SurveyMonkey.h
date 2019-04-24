#pragma once

#include "Service.h"
#include "SocketWorker.h"

class SurveyMonkey :
	public Service::Monkey
{
public:
	SurveyMonkey();
	~SurveyMonkey();

	virtual Json::Value doPost(Json::Value props, SocketWorker& socketWorker);
};
