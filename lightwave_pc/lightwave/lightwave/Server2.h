#pragma once

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

extern class AcceptorThread;

class Server2
{
public:
	Server2();
	~Server2();

	void start();
	void updateAcceptance() const;

private:
	AcceptorThread* m_acceptorThread = nullptr;
};

