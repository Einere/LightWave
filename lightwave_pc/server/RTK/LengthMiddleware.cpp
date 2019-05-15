#include "stdafx.h"
#include "SocketWorker.h"
#include "LengthMiddleware.h"

namespace Service {
	LengthMiddleware::LengthMiddleware()
		:Monkey("length")
	{
	}

	LengthMiddleware::~LengthMiddleware()
	{
	}

	Json::Value LengthMiddleware::Handle(Json::Value props, SocketWorker & socketWorker)
	{
		int length = props["data"]["length"].asInt();
		socketWorker.beginBlob(length); 
		return Service::NoResponse();
	}
}