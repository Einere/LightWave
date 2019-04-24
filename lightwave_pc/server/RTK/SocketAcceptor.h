#pragma once

class WorkerManager;

class SocketAcceptor : public CSocket
{
public:
	SocketAcceptor();
	~SocketAcceptor();

	virtual void OnAccept(int nErrorCode);

private:
};

