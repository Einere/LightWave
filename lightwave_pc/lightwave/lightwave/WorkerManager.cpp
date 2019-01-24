#include "stdafx.h"
#include "WorkerManager.h"
#include "ServerWorker.h"
#include "Server.h"


WorkerManager::WorkerManager()
{

}

WorkerManager::~WorkerManager()
{
	int workerCount = workers.size();
	for (int i = workerCount - 1; i >= 0; --i) {
		remove(*workers[i]);
	}
}

bool WorkerManager::isBusy()
{
	return (workers.size() >= maxWorkersCount);
}

bool WorkerManager::employWorker(SOCKET sock)
{
	if (isBusy()) {
		return false;
	}
	
	ServerWorker* worker = new ServerWorker(sock, this);
	if (worker->work() == nullptr) {
		return false;
	}

	workers.push_back(worker);

	printf("workers count increasing: %d\n", workers.size());

	return true;
}

void WorkerManager::notifyStatus(const ServerWorker & worker)
{
	if (!worker.isAlive()) {
		assert(remove(worker));
	}
}

void WorkerManager::clear()
{
	for (int i = workers.size() - 1; i >= 0; --i) {
		workers[i]->cleanUp();
		remove(*workers[i]);
		workers[i] = nullptr;
	}
}

const ClientList& WorkerManager::getWorkers() const
{
	return workers;
}

bool WorkerManager::remove(const ServerWorker & worker)
{
	int targetIndex = -1;
	int workerCount = workers.size();
	for (int i = 0; i < workerCount; ++i) {
		if (worker.getThread() == workers[i]->getThread()) {
			targetIndex = i;
			break;
		}
	}
	
	if (targetIndex == -1) {
		return false;
	}

	delete workers[targetIndex];

	printf("worker[%d] removed\n", targetIndex);

	if (targetIndex != workerCount - 1) {
		workers[targetIndex] = workers[workerCount - 1];
		workers[workerCount - 1] = nullptr;
	}

	--workerCount;

	return true;
}

