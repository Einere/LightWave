#pragma once

#include "Service.h"

class WorkerManager;

class SocketWorker :
	public CSocket
{
public:
	SocketWorker(WorkerManager* pWorkerManager = NULL);
	~SocketWorker();

	void setWorkerManager(WorkerManager* pWorkerManager);

	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);

private:
	Service::RequestResolver m_requestResolver;

	std::string readIn();
	int getJsonSize(std::string stringContainingKeyOfSize);

	WorkerManager* m_pWorkerManager = NULL;
};

