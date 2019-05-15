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
		Logger::Err("������ Ip�ּ�[%s]�� port[%d]���� �� ���� ���� �õ��� Ȯ�� �� => ����", ip, port);
		return;
	}
	
	pWorker = std::make_shared<SocketWorker>();
	Accept(*pWorker);
	
	auto pManager = WorkerManager::GetInstance();
	pManager->AppendWorker(pWorker);
	
	Listen();
}
