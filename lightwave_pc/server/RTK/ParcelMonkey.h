#pragma once

#include "Service.h"
#include "SocketWorker.h"

class ParcelMonkey :
	public Service::Monkey
{
public:
	ParcelMonkey();
	~ParcelMonkey();

	virtual Json::Value doGet(Json::Value props, SocketWorker& socketWorker);
};

