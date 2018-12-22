#pragma once

extern class ServerWorker;

class WorkerManager
{
public:
	WorkerManager();
	~WorkerManager();

	bool isBusy();
	bool employWorker(SOCKET sock);

	void notifyStatus(const ServerWorker& worker);
	
	void clear();

private:
	bool remove(const ServerWorker& worker);

	ServerWorker* workers[3];
	int workerCount = 0;

	const int maxWorkersCount = 3;
};

