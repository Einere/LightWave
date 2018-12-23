#include "stdafx.h"
#include "WorkerManager.h"
#include "ServerWorker.h"


WorkerManager::WorkerManager()
{
}

WorkerManager::~WorkerManager()
{
	for (int i = workerCount - 1; i >= 0; --i) {
		remove(*workers[i]);
	}
}

bool WorkerManager::isBusy()
{
	return (workerCount >= maxWorkersCount);
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

	workers[workerCount] = worker;
	++workerCount;

	printf("workers count increasing: %d\n", workerCount);

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
	for (int i = workerCount - 1; i >= 0; --i) {
		remove(*workers[i]);
		workers[i] = nullptr;
	}

	workerCount = 0;
}

bool WorkerManager::remove(const ServerWorker & worker)
{
	int targetIndex = -1;
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

