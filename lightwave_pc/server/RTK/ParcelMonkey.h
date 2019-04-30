#pragma once

#include "Service.h"
#include "SocketWorker.h"

class ParcelMonkey :
	public Service::Monkey
{
public:
	ParcelMonkey();
	~ParcelMonkey();

	virtual Json::Value DoGet(Json::Value props, SocketWorker& socketWorker);
};

