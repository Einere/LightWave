#pragma once

#define DEFAULT_BUFLEN 512

extern class WorkerManager;

class ServerWorker
{
public:
	ServerWorker(const SOCKET AcceptedClientSocket, WorkerManager* workerManager);
	~ServerWorker();

	CWinThread* work();
	void cleanUp();

	const char* getIPAddress() const;
	const SOCKET getClientSocket() const;
	CWinThread* getThread() const;
	WorkerManager* getManager() const;

	bool isAlive() const;

private:
	static UINT TaskFunc(LPVOID pParam);

	WorkerManager* manager = nullptr;

	const SOCKET ClientSocket;
	CWinThread *pThread = nullptr;

	bool bDeprecated = false;
};