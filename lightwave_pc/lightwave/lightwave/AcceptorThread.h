#pragma once

#include <thread>
#include <mutex>
#include <queue>

extern class Server2;

class AcceptorThread
{
public:
	AcceptorThread(Server2& server, SOCKET listenSocket);
	~AcceptorThread();

	void run();
	void startAccepting();
	void close();
	SOCKET popAndGet();
	bool hasTheUnhandled();
protected:
	void notifyAcceptance();

	std::queue<SOCKET> m_acceptedClientSockets;
	bool isRunning = false;

	std::mutex acceptorMtx;

private:
	const Server2& m_server;
	const SOCKET m_listenSock;
	std::thread* m_th = nullptr;
};

