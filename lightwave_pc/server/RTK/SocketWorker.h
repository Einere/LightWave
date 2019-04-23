#pragma once

#include "Service.h"
#include "Worker.h"

class WorkerManager;

class SocketWorker :
	public CSocket
{
public:
	SocketWorker(WorkerManager* pWorkerManager = NULL);
	~SocketWorker();

	void setWorkerManager(WorkerManager* pWorkerManager);
	void setWorkerName(CString workerName);
	CString getWorkerName();

	void setAuthorized();
	bool isAuthorized() const;

	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);

	void notifyUpdate() const;

private:
	Service::RequestResolver m_requestResolver;

	std::string readIn();

	Workers::Worker m_worker;
	int getJsonSize(std::string stringContainingKeyOfSize);

	WorkerManager* m_pWorkerManager = NULL;
};

