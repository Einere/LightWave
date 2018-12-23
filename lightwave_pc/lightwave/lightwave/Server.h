#pragma once

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#include "WorkerManager.h"

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
	bool isRunning() const;

private:
	SOCKET ListenSocket = INVALID_SOCKET;
	CWinThread* pThread = nullptr;
	WorkerManager* workerManager;
	bool bRunning = false;
};

UINT acceptFunc(LPVOID pParam);