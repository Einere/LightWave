#include "stdafx.h"
#include "WorkerManager.h"
#include "MainFrm.h"
#include "SocketWorker.h"

SocketWorker::SocketWorker(WorkerManager* pWorkerManager) {
	m_pWorkerManager = pWorkerManager;
}


SocketWorker::~SocketWorker()
{
}

void SocketWorker::setWorkerManager(WorkerManager * pWorkerManager)
{
	m_pWorkerManager = pWorkerManager;
}

void SocketWorker::OnAccept(int nErrorCode)
{
	m_pWorkerManager->OnAccept(nErrorCode);
}

void SocketWorker::OnReceive(int nErrorCode)
{
	CString ipAddress;
	UINT port;
	Log::log("들어왔어");
	GetPeerName(ipAddress, port);
	m_pWorkerManager->OnReceive(ipAddress, port, nErrorCode);
}

void SocketWorker::OnClose(int nErrorCode)
{
	CString ipAddress;
	UINT port;
	GetPeerName(ipAddress, port);
	m_pWorkerManager->OnClose(ipAddress, port, nErrorCode);
}
