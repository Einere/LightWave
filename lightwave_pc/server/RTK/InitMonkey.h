#pragma once

#include "Service.h"
#include "WorkerManager.h"

class InitMonkey : public Service::Monkey
{
public:
	InitMonkey();
	~InitMonkey();

	virtual Json::Value doPost(Json::Value props);
};

