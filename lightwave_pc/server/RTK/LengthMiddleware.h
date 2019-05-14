#pragma once

#include "Service.h"

namespace Service {
	class LengthMiddleware : public Service::Monkey
	{
	public:
		LengthMiddleware();
		~LengthMiddleware();

		// override
		Json::Value Handle(Json::Value props, SocketWorker& socketWorker);
	};
}
