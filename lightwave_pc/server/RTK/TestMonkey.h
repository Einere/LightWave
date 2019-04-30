#pragma once
#include "Service.h"
#include "SocketWorker.h"

class TestMonkey :
	public Service::Monkey
{
public:
	TestMonkey();
	~TestMonkey();

	virtual Json::Value DoGet(Json::Value props, SocketWorker& socketWorker);
};

