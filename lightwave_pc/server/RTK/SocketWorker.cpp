#include "stdafx.h"
#include "WorkerManager.h"
#include "MainFrm.h"
#include "SocketWorker.h"

SocketWorker::SocketWorker( WorkerManager* pWorkerManager) {
	m_pWorkerManager = pWorkerManager;
}

SocketWorker::~SocketWorker()
{
}

void SocketWorker::SetWorkerManager(WorkerManager * pWorkerManager)
{
	m_pWorkerManager = pWorkerManager;
}

Workers::Worker SocketWorker::GetWorker() const
{
	return m_worker;
}

void SocketWorker::SetWorkerName(CString workerName)
{
	m_worker.name = workerName;
	NotifyUpdate();
}

CString SocketWorker::GetWorkerName()
{
	return m_worker.name;
}

void SocketWorker::SetAuthorized()
{
	m_worker.authorized = true;

	/* workaround */
	GetPeerName(m_worker.ip, m_worker.port);
}

bool SocketWorker::IsAuthorized() const
{
	return m_worker.authorized;
}

void SocketWorker::OnReceive(int nErrorCode)
{
	const std::string data = readIn();
	Logger::Log("request: %s", data.c_str());
	
	std::string response = m_requestResolver.Resolve(*this, data);
	response += '\n';
	Logger::Log("response: %s", response.c_str());

	auto res = response.c_str();

	int result = this->Send((void*)(res), response.length(), sends);
	if (SOCKET_ERROR == result) {
		Logger::Log("응답 실패");
		return;
	}

	Logger::Log("Sent: %d bytes", result);
}

void SocketWorker::OnClose(int nErrorCode)
{
	CString ipAddress;
	UINT port;
	GetPeerName(ipAddress, port);
	WorkerManager::GetInstance()->OnClose(ipAddress, port, nErrorCode);
}

void SocketWorker::NotifyUpdate() const
{
	WorkerManager::GetInstance()->Update();
}

std::string SocketWorker::readIn()
{
	std::string buf;

	const int BLOCK_SIZE = 1024;
	int receivedLength = 0;
	do {
		char block[BLOCK_SIZE];
		receivedLength = Receive((void*)block, BLOCK_SIZE);
		buf.append(block, receivedLength);
	} while (receivedLength == 1024 && buf[buf.size()-1]!=0);

	return buf;
}

int SocketWorker::GetJsonSize(std::string stringContainingKeyOfSize)
{
	const std::string s = stringContainingKeyOfSize;
	const std::string key = "\"size:\"";
	size_t valueStart = s.find_first_of(key, 0) + key.size();
	size_t valueEnd = s.find_first_of(',', valueStart);
	return atoi(s.substr(valueStart, valueEnd - valueStart).c_str());
}
