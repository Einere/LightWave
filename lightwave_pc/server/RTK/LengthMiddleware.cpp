#include "stdafx.h"
#include "LengthMiddleware.h"
#include "SocketWorker.h"

namespace Service {

	LengthMiddleware::LengthMiddleware()
		:Monkey("length")
	{
	}


	LengthMiddleware::~LengthMiddleware()
	{
	}

	Json::Value Service::LengthMiddleware::Handle(Json::Value props, SocketWorker & socketWorker)
	{
		int length = props["data"]["length"].asInt();
		socketWorker.beginBlob(length);
		return Service::Success("");
	}

}