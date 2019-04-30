#pragma once

#include "Service.h"
#include "WorkerManager.h"
#include "SocketWorker.h"

class InitMonkey : public Service::Monkey
{
public:
	InitMonkey();
	~InitMonkey();

	virtual Json::Value DoPost(Json::Value props, SocketWorker& socketWorker);
};

