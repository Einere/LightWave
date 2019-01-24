#include "stdafx.h"

#include <json.h>
#include <thread>

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
}

const char * ServerWorker::getIPAddress() const
{
	sockaddr_in addr;
	int len = sizeof(addr);

	getsockname(ClientSocket, (sockaddr*)&addr, &len);
	return inet_ntoa(addr.sin_addr);
}

const std::vector<wchar_t> ServerWorker::getIPAddressW() const
{
	const char* ipAddress = getIPAddress();
	size_t length = strlen(ipAddress);
	wchar_t ipAddressW[20];

	mbstowcs_s(&length, ipAddressW, ipAddress, length);

	std::vector<wchar_t> ret(ipAddressW, &ipAddressW[length]+1);
	/*for (int i = 0; i < length; ++i) {
		ret.push_back(ipAddressW[i]);
	}*/

	return ret;
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

	Json::Reader reader;

	// Receive until the peer shuts down the connection
	do {
		iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			printf("Bytes received: %d\n", iResult);

			// Echo the buffer back to the sender
			iSendResult = send(ClientSocket, recvbuf, iResult, 0);
			if (iSendResult == SOCKET_ERROR) {
				printf("send failed with error: %d\n", WSAGetLastError());
				break;
			}

			recvbuf[iResult] = '\0';
			Json::Value jsonData;
			reader.parse(recvbuf, jsonData);

			std::cout << "===========================" << std::endl;
			std::cout << "이름: " << jsonData.get("name", "noname") << std::endl;
			std::cout << "나이: " << jsonData.get("age", "noage") << std::endl;
			std::cout << "===========================" << std::endl;

			printf("msg from [%s]: <%s>\n", worker->getIPAddress(), recvbuf);
		}
		else if (iResult == 0)
			break;
		else {
			printf("recv failed with error: %d\n", WSAGetLastError());
			break;
		}

	} while (iResult > 0);

	worker->cleanUp();
	worker->getManager()->notifyStatus(*worker);

	printf("Connection closing...\n");

	return 0;
}


