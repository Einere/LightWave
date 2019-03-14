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

void SocketWorker::setWorkerManager(WorkerManager * pWorkerManager)
{
	m_pWorkerManager = pWorkerManager;
}

void SocketWorker::OnReceive(int nErrorCode)
{
	Log::log("요청 들어옴. 처리 중...");
	const std::string json = readIn();

	//Log::log("받은 내용: %s", json.c_str());
	//Log::log("길이: %d", json.size());

	// 아래 코드는 요청을 처리하고 응답하는 부분임
	// 요청으로 들어온 문자열을 출력만 하고 끝내기 위해 임시적으로 주석처리함

	//m_pWorkerManager->OnReceive(this, json, nErrorCode);
	//Log::log("애플리케이션 파트 처리 끝...");
		
	const std::string response = m_requestResolver.resolve(this, json);
	Log::log("response: %s", response.c_str());

	this->Send((void*)(&response), response.size(), sends);
}

void SocketWorker::OnClose(int nErrorCode)
{
	CString ipAddress;
	UINT port;
	GetPeerName(ipAddress, port);
	m_pWorkerManager->OnClose(ipAddress, port, nErrorCode);
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

int SocketWorker::getJsonSize(std::string stringContainingKeyOfSize)
{
	const std::string s = stringContainingKeyOfSize;
	const std::string key = "\"size:\"";
	size_t valueStart = s.find_first_of(key, 0) + key.size();
	size_t valueEnd = s.find_first_of(',', valueStart);
	return atoi(s.substr(valueStart, valueEnd - valueStart).c_str());
}
