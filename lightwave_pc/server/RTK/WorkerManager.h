#pragma once

#include "SocketWorker.h"
#include "SocketAcceptor.h"
#include "StatePane.h"

class SocketRecipient;
class SocketAcceptor;

enum Host {
	PORT = 8080,
	BUFLEN = 1024
};

class WorkerManager
{
public:
	~WorkerManager();

	/*const SocketRecipient* getRecepient() const;
	void setRecepient(SocketRecipient* recep);*/
	void setSocketStatePane(StatePane* dlg);

	std::shared_ptr<SocketWorker> getWorkerOrNull(const CString& ipAddress, UINT port) const;
	const std::vector<std::shared_ptr<SocketWorker>>& getWorkers();

	void startServer();
	//void startServer(SocketRecipient* recep);

	void stopServer();

	void OnAccept(std::shared_ptr<SocketWorker> pNewWorker);

	/* Deprecated: 이전 구현에서 사용되는 함수 */
	void OnReceive(SocketWorker * pSocketWorker, std::string json, int errorCode);
	void OnClose(const CString& ipAddress, UINT port, int errorCode);

	bool isListening() const;

	void closeAll();

	bool inspect(std::shared_ptr<SocketWorker> target);

	void update();
	void notify();

private:
	//SocketRecipient* m_pRecepient = NULL;

	SocketAcceptor m_acceptor;
	std::vector<std::shared_ptr<SocketWorker>> m_workers;

	StatePane* m_pStatePane = NULL;

	bool m_isListening = false;

protected:
	bool removeOrFalse(const CString& ipAddress, UINT port);

protected:
	WorkerManager();
	static WorkerManager* m_pThis;

public:
	static WorkerManager* GetInstance();
	static void ReleaseInstance();
};

