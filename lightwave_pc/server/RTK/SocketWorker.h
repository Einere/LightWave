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
	void setWorkerName(CString workerName);
	CString getWorkerName();

	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);

	void notifyUpdate() const;

private:
	Service::RequestResolver m_requestResolver;

	std::string readIn();
	CString m_workerName;
	int getJsonSize(std::string stringContainingKeyOfSize);

	WorkerManager* m_pWorkerManager = NULL;
};

