#pragma once
#include "Service.h"
#include "SocketWorker.h"

class TestMonkey :
	public Service::Monkey
{
public:
	TestMonkey();
	~TestMonkey();

	virtual Json::Value doGet(Json::Value props, SocketWorker& socketWorker);
};

