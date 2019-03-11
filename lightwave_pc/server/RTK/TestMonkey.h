#pragma once
#include "Service.h"
class TestMonkey :
	public Service::Monkey
{
public:
	TestMonkey();
	~TestMonkey();

	virtual Json::Value doGet(Json::Value props);
};

