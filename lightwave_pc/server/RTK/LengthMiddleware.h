#pragma once

#include "Service.h"
#include "SocketWorker.h"

namespace Service {
	/*
	Middleware: 일반적인 요청처리 과정으로 들어가기 전에 내용을 한 번 검사하여 특별한 일을 수행
	현재 미들웨어는 LengthMiddleware만 존재

	큰 데이터를 보내기 전에 전송 데이터 크기 전달을 목적으로 하는 요청을 담당
	해당 요청을 보낸 클라이언트에 한하여 지정된 길이를 전부 받을 때까지 요청을 처리하지 않고 읽어들임.
	*/
	class LengthMiddleware : public Service::Monkey
	{
	public:
		LengthMiddleware();
		~LengthMiddleware();

		// override
		Json::Value Handle(Json::Value props, SocketWorker& socketWorker);
	};
}
