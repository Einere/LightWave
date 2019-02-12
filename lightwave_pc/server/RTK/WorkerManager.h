#pragma once

#include "SocketWorker.h"

class SocketRecipient;


enum Host {
	PORT = 8080,
	BUFLEN = 1024
};

class WorkerManager
{
public:
	WorkerManager(SocketRecipient* recep = NULL);
	~WorkerManager();

	const SocketRecipient* getRecepient() const;
	void setRecepient(SocketRecipient* recep);

	std::vector<std::shared_ptr<SocketWorker>> getWorkers() const;

	void startServer();
	void startServer(SocketRecipient* recep);

	void stopServer();

	void OnAccept(int errorCode);
	void OnReceive(const CString& ipAddress, UINT port, int errorCode);
	void OnClose(const CString& ipAddress, UINT port, int errorCode);

	bool isListening() const;

	void closeAll();

	bool inspect(std::shared_ptr<SocketWorker> target);

private:
	SocketRecipient* m_pRecepient = NULL;

	SocketWorker m_acceptor;
	std::vector<std::shared_ptr<SocketWorker>> m_workers;

	bool m_isListening = false;

protected:
	std::shared_ptr<SocketWorker> findWorkerOrNull(const CString& ipAddress, UINT port) const;
	bool removeOrFalse(const CString& ipAddress, UINT port);
};

