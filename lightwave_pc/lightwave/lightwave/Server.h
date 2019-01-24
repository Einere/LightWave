#pragma once

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <vector>

extern class Dashboard;
extern class WorkerManager;
extern class ServerWorker;

typedef std::vector<ServerWorker*> ClientList;

#define DEFAULT_PORT "8080"
#define MAX_CLIENTS 3

class Server
{
public:
	Server();
	~Server();

	//int doSomething();
	void startServer();
	void stopServer();

	const SOCKET getListenSocket() const;
	const CWinThread* getThread() const;
	const WorkerManager* getWorkerManager();
	WorkerManager* getWorkerManager() const;
	const ClientList& getWorkers() const;
	bool isRunning() const;
	Dashboard* getDashboard() const;
	void setDashboard(Dashboard* dashboard);

private:
	SOCKET ListenSocket = INVALID_SOCKET;
	CWinThread* pThread = nullptr;
	WorkerManager* workerManager;
	bool bRunning = false;
	Dashboard* dashboard = nullptr;
};

UINT acceptFunc(LPVOID pParam);