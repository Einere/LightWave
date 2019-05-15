#pragma once


#include "SocketWorker.h"
#include "SocketAcceptor.h"
#include "StatePane.h"

#define BUFLEN 1024

class WorkerManager
{
public:
	~WorkerManager();

	void SetSocketStatePane(StatePane* dlg);

	std::shared_ptr<Service::SocketWorker> GetWorkerOrNull(CString name) const;
	std::shared_ptr<Service::SocketWorker> GetWorkerOrNull(const CString& ipAddress, UINT port) const;
	const std::vector<std::shared_ptr<Service::SocketWorker>>& GetWorkers();

	void StartServer();
	//void startServer(SocketRecipient* recep);

	void StopServer();


	void AppendWorker(std::shared_ptr<Service::SocketWorker> pNewWorker);
	void DeleteWorker(const CString& ipAddress, UINT port);
	void DeleteWorker(CString name);

	/* Deprecated: 이전 구현에서 사용되는 함수 */
	void OnReceive(Service::SocketWorker * pSocketWorker, std::string json, int errorCode);

	bool IsListening() const;

	void CloseAll();

	bool Inspect(std::shared_ptr<Service::SocketWorker> target);

	void Update();
	void Notify();

	void SetPort(UINT port);
	UINT GetPortNow() const;
	UINT GetPort() const;
	void GetIpAddrs(std::vector<CString>& ips) const;
	void GetIpAddrAndPort(CString& Addr, UINT& port) const;

private:
	Service::SocketAcceptor m_acceptor;
	std::vector<std::shared_ptr<Service::SocketWorker>> m_workers;
	StatePane* m_pStatePane = NULL;

	UINT m_port = 8080;
	UINT m_nextPort = 0;

	bool m_isListening = false;

protected:
	bool RemoveOrFalse(const CString& ipAddress, UINT port);

protected:
	WorkerManager();
	static WorkerManager* m_pThis;

public:
	static WorkerManager* GetInstance();
	static void ReleaseInstance();
};
