#include "stdafx.h"
#include "SocketAcceptor.h"
#include "WorkerManager.h"
#include "SocketWorker.h";


SocketAcceptor::SocketAcceptor(WorkerManager* pManager)
	: m_pManager(pManager)
{
}


SocketAcceptor::~SocketAcceptor()
{
}

void SocketAcceptor::OnAccept(int nErrorCode)
{
	auto pWorker = std::make_shared<SocketWorker>();
	Accept(*pWorker);
	
	m_pManager->OnAccept(pWorker);
	
	Listen();
}
