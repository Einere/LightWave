#pragma once

#include "Service.h"
#include "SocketWorker.h"


namespace Service {
	class InitMonkey : public Service::Monkey
	{
	public:
		InitMonkey();
		~InitMonkey();

		virtual Json::Value DoPost(Json::Value props, SocketWorker& socketWorker);
	};
}