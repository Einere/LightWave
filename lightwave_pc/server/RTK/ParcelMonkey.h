#pragma once

#include "Service.h"

class ParcelMonkey :
	public Service::Monkey
{
public:
	ParcelMonkey();
	~ParcelMonkey();

	virtual Json::Value doGet(Json::Value props);
};

