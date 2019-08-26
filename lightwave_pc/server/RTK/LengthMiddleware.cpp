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

		Json::Value result;
		result["status"] = 2;
		return Service::Success(result);
	}
}