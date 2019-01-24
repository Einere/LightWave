#include "stdafx.h"
#include "Server.h"
#include "Dashboard.h"
#include "WorkerManager.h"

Server::Server()
{
	workerManager = new WorkerManager();
}

Server::~Server()
{
	delete workerManager;
}

void Server::startServer()
{
	bRunning = true;

	int iResult;
	WSADATA wsaData;

	struct addrinfo *result = NULL;
	struct addrinfo hints;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	assert(iResult == 0);

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	assert(iResult == 0);

	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	assert(ListenSocket != INVALID_SOCKET);

	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	assert(iResult != SOCKET_ERROR);

	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);
	assert(iResult != SOCKET_ERROR);

	pThread = AfxBeginThread(acceptFunc, (LPVOID)this);
}

void Server::stopServer()
{
	bRunning = false;
	workerManager->clear();
	closesocket(ListenSocket);
	WSACleanup();
}

const SOCKET Server::getListenSocket() const
{
	return ListenSocket;
}

const CWinThread * Server::getThread() const
{
	return pThread;
}

const WorkerManager * Server::getWorkerManager()
{
	return workerManager;
}

WorkerManager * Server::getWorkerManager() const
{
	return workerManager;
}

const ClientList& Server::getWorkers() const
{
	return workerManager->getWorkers();
}

bool Server::isRunning() const
{
	return bRunning;
}

Dashboard * Server::getDashboard() const
{
	return dashboard;
}

void Server::setDashboard(Dashboard * dashboardParam)
{
	dashboard = dashboardParam;
}

UINT acceptFunc(LPVOID pParam)
{
	const Server* server = (Server*)pParam;
	const SOCKET ListenSocket = server->getListenSocket();
	WorkerManager* manager = server->getWorkerManager();

	// Accept a client socket
	bool isServerRunning = false;
	while (isServerRunning = server->isRunning()) {
		if (manager->isBusy()) {
			continue;
		}

		printf("waiting for a request to accept...\n");
		SOCKET ClientSocket = accept(ListenSocket, NULL, NULL);
		/*if (ClientSocket != INVALID_SOCKET) {
			printf("is server running: %d", isServerRunning);
		}*/
		assert(ClientSocket != INVALID_SOCKET);

		manager->employWorker(ClientSocket);
		if (server->getDashboard() != nullptr) {
			server->getDashboard()->updateClientList(server);
		}

	}

	return 0;
}
