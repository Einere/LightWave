#include "stdafx.h"
#include "SocketAcceptor.h"
#include "WorkerManager.h"
#include "SocketWorker.h";

namespace Service {
	SocketAcceptor::SocketAcceptor()
	{
	}


	SocketAcceptor::~SocketAcceptor()
	{
		Close();
	}

	void SocketAcceptor::OnAccept(int nErrorCode)
	{
		auto pWorker = std::make_shared<SocketWorker>();
		Accept(*pWorker);

		auto pManager = WorkerManager::GetInstance();
		pManager->AppendWorker(pWorker);

		/*
		Accept된 클라이언트는 방금 생성된 SocketWorker가 전담 마크한다.
		나는 다른 연결 요청을 받기위해 Listen 한다.
		*/
		Listen();
	}
}