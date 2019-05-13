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

	void SetWorkerManager(WorkerManager* pWorkerManager);

	Workers::Worker GetWorker() const;

	void SetWorkerName(CString workerName);
	CString GetWorkerName();

	void SetAuthorized();
	bool IsAuthorized() const;

	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);

	void NotifyUpdate() const;

	void beginBlob(int size);
	void endBlob();

private:
	Service::RequestResolver m_requestResolver;

	std::string readIn();
	std::string m_data;
	int m_blobSize = 0;

	Workers::Worker m_worker;
	int GetJsonSize(std::string stringContainingKeyOfSize);

	WorkerManager* m_pWorkerManager = NULL;
};

