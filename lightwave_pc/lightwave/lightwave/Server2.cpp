#include "stdafx.h"
#include "Server2.h"
#include "AcceptorThread.h"

#define DEFAULT_PORT "8080"

Server2::Server2()
{
}


Server2::~Server2()
{
}

void Server2::start()
{
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
	SOCKET listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	assert(listenSocket != INVALID_SOCKET);

	iResult = bind(listenSocket, result->ai_addr, (int)result->ai_addrlen);
	assert(iResult != SOCKET_ERROR);

	freeaddrinfo(result);

	iResult = listen(listenSocket, SOMAXCONN);
	assert(iResult != SOCKET_ERROR);

	m_acceptorThread = new AcceptorThread(*this, listenSocket);
}

void Server2::updateAcceptance() const
{
	assert(m_acceptorThread);

	while (m_acceptorThread->hasTheUnhandled()) {
		SOCKET acceptedSocket = m_acceptorThread->popAndGet();
		
		/* 억셉트한 소켓에 대해 스레드를 만드는 등의 처리 코드 (미구현) */
	}
}
