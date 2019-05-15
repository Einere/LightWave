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
		Accept�� Ŭ���̾�Ʈ�� ��� ������ SocketWorker�� ���� ��ũ�Ѵ�.
		���� �ٸ� ���� ��û�� �ޱ����� Listen �Ѵ�.
		*/
		Listen();
	}
}