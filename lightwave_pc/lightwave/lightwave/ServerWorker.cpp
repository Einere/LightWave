#include "stdafx.h"
#include "ServerWorker.h"
#include "WorkerManager.h"


ServerWorker::ServerWorker(const SOCKET AcceptedClientSocket, WorkerManager * workerManager)
	:ClientSocket(AcceptedClientSocket)
{
	manager = workerManager;
}

ServerWorker::~ServerWorker()
{
	//delete pThread;
}

CWinThread* ServerWorker::work()
{
	pThread = AfxBeginThread(TaskFunc, (LPVOID)this);
	assert(pThread != nullptr);
	
	return pThread;
}

void ServerWorker::cleanUp()
{
	int iResult = shutdown(ClientSocket, SD_SEND);
	assert(iResult != SOCKET_ERROR);

	closesocket(ClientSocket);

	bDeprecated = true;
	
	manager->notifyStatus(*this);
}

const char * ServerWorker::getIPAddress() const
{
	sockaddr_in addr;
	int len = sizeof(addr);

	getsockname(ClientSocket, (sockaddr*)&addr, &len);
	return inet_ntoa(addr.sin_addr);
}

CWinThread * ServerWorker::getThread() const
{
	return pThread;
}

WorkerManager * ServerWorker::getManager() const
{
	return manager;
}

bool ServerWorker::isAlive() const
{
	return !bDeprecated;
}

const SOCKET ServerWorker::getClientSocket() const
{
	return ClientSocket;
}

UINT ServerWorker::TaskFunc(LPVOID pParam)
{
	ServerWorker* worker = (ServerWorker*)pParam;
	SOCKET ClientSocket = worker->getClientSocket();

	int iResult;
	int iSendResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	// Receive until the peer shuts down the connection
	do {

		iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			printf("Bytes received: %d\n", iResult);

			// Echo the buffer back to the sender
			iSendResult = send(ClientSocket, recvbuf, iResult, 0);
			if (iSendResult == SOCKET_ERROR) {
				printf("send failed with error: %d\n", WSAGetLastError());
				worker->cleanUp();
				return 1;
			}

			recvbuf[iResult] = '\0';
			printf("msg from [%s]: %s\n", worker->getIPAddress(), recvbuf);
		}
		else if (iResult == 0)
			printf("Connection closing...\n");
		else {
			printf("recv failed with error: %d\n", WSAGetLastError());
			worker->cleanUp();
			return 1;
		}

	} while (iResult > 0);

	return 0;
}


