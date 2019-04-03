#pragma once

#include "Service.h"

class SurveyMonkey :
	public Service::Monkey
{
public:
	SurveyMonkey();
	~SurveyMonkey();

	virtual Json::Value doPost(Json::Value props);
};
