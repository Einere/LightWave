#pragma once

class WorkerManager;

class SocketAcceptor : public CSocket
{
public:
	SocketAcceptor(WorkerManager* pManager);
	~SocketAcceptor();

	virtual void OnAccept(int nErrorCode);

private:
	std::shared_ptr<WorkerManager> m_pManager;
};

