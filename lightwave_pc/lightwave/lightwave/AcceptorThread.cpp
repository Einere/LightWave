#include "stdafx.h"
#include "AcceptorThread.h"
#include "Server2.h"
#include "Common.h"
#include <mutex>
#include <thread>
#include <chrono>


AcceptorThread::AcceptorThread(Server2 & server, SOCKET listenSocket)
	: m_server(server), m_listenSock(listenSocket)
{
		
}

AcceptorThread::~AcceptorThread()
{
	while (m_acceptedClientSockets.empty()) {
		const SOCKET unhandled = m_acceptedClientSockets.front();
		/* 각 소켓에 대해 연결을 끊는 부분 (미구현) */
	}

	if (m_th) {
		delete m_th;
	}
}

void AcceptorThread::run()
{
	m_th = new std::thread(&AcceptorThread::startAccepting, this);
}

void AcceptorThread::startAccepting()
{
	std::unique_lock<std::mutex> lock(acceptorMtx);
	isRunning = true;
	lock.unlock();

	while (isRunning) {

		printf("waiting for a request to accept...\n");
		SOCKET ClientSocket = accept(m_listenSock, NULL, NULL);
		/*if (ClientSocket != INVALID_SOCKET) {
			printf("is server running: %d", isServerRunning);
		}*/
		assert(ClientSocket != INVALID_SOCKET);
		notifyAcceptance();
	}
}

void AcceptorThread::close()
{
	std::unique_lock<std::mutex> lock(acceptorMtx);

	isRunning = false;
}

SOCKET AcceptorThread::popAndGet()
{
	SOCKET socket = m_acceptedClientSockets.front();
	m_acceptedClientSockets.pop();
	return socket;
}

bool AcceptorThread::hasTheUnhandled()
{
	return !m_acceptedClientSockets.empty();
}

void AcceptorThread::notifyAcceptance()
{
	m_server.updateAcceptance();
}
