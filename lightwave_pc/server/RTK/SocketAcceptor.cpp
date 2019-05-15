#include "stdafx.h"
#include "SocketAcceptor.h"
#include "WorkerManager.h"
#include "SocketWorker.h";


SocketAcceptor::SocketAcceptor()
{
}


SocketAcceptor::~SocketAcceptor()
{
	Close();
}

void SocketAcceptor::OnAccept(int nErrorCode)
{
	CString ip;
	UINT port;
	GetSockName(ip, port);

	auto pWorker = WorkerManager::GetInstance()->GetWorkerOrNull(ip, port);
	if (pWorker) {
		Logger::Err("동일한 Ip주소[%s]와 port[%d]에서 두 번의 연결 시도가 확인 됨 => 거절", ip, port);
		return;
	}
	
	pWorker = std::make_shared<SocketWorker>();
	Accept(*pWorker);
	
	auto pManager = WorkerManager::GetInstance();
	pManager->AppendWorker(pWorker);
	
	Listen();
}
