#pragma once

class WorkerManager;

class SocketWorker :
	public CSocket
{
public:
	SocketWorker(WorkerManager* pWorkerManager = NULL);
	~SocketWorker();

	void setWorkerManager(WorkerManager* pWorkerManager);

	virtual void OnAccept(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);

private:
	WorkerManager* m_pWorkerManager = NULL;
};

