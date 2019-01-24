#pragma once

#include "Server.h"

extern class ServerWorker;

class WorkerManager
{
public:
	WorkerManager();
	~WorkerManager();

	bool isBusy();
	bool employWorker(SOCKET sock);

	void notifyStatus(const ServerWorker& worker);
	void fire(const ServerWorker& worker);
	
	void clear();

	const ClientList& getWorkers() const;

private:
	bool remove(const ServerWorker& worker);

	ClientList workers;

	const int maxWorkersCount = 3;
};

