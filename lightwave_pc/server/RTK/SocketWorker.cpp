#include "stdafx.h"
#include "TextEncoding.h"
#include "WorkerManager.h"
#include "MainFrm.h"
#include "SocketWorker.h"
#include "LengthMiddleware.h"

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
	GetPeerName(m_worker.ip, m_worker.port);
}

bool SocketWorker::IsAuthorized() const
{
	return m_worker.authorized;
}

void SocketWorker::OnReceive(int nErrorCode)
{
	m_data += readIn();
	if (!isEndOfRequest()) {
		// 요청의 끝을 아직 만나지 못했으므로 응답하지않고 다음 패킷을 기다린다.
		return;
	}

	Logger::Log("request size: %d bytes", m_data.size());
	Logger::Log("request: %s", m_data.c_str());
	
	std::string response = m_requestResolver.Resolve(*this, m_data);
	if (response == Service::NO_RESPONSE) return;
	response += '\n';

	std::string responseU8 = UTF8Encoding::gogoUTF8(response);

	int sentSizeOrError = this->Send((void*)(responseU8.c_str()), responseU8.size(), sends);
	if (SOCKET_ERROR == sentSizeOrError) {
		Logger::Log("응답 실패");
		return;
	}

	Logger::Log("response size: %d bytes", sentSizeOrError);
	Logger::Log("response: %s", response.c_str());
	m_data.clear();
}

void SocketWorker::OnClose(int nErrorCode)
{
	CString ipAddress;
	UINT port;
	GetPeerName(ipAddress, port);
	WorkerManager::GetInstance()->DeleteWorker(ipAddress, port);
}

void SocketWorker::NotifyUpdate() const
{
	WorkerManager::GetInstance()->Update();
}

void SocketWorker::beginBlob(int size)
{
	m_data.clear();
	m_blobSize = size;
}

void SocketWorker::endBlob()
{
	m_data.clear();
	m_blobSize = 0;
}

bool SocketWorker::isEndOfRequest() const
{
	return !(m_blobSize > 0);
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

	if (m_blobSize > 0) {
		m_blobSize -= receivedLength;
	}

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
