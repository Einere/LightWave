#include "stdafx.h"
#include "WorkerManager.h"
#include "SocketWorker.h"
#include "SocketRecipient.h"


WorkerManager::WorkerManager(SocketRecipient* recep)
{
	m_pRecepient = recep;
}


WorkerManager::~WorkerManager()
{
}

const SocketRecipient* WorkerManager::getRecepient() const
{
	return m_pRecepient;
}

void WorkerManager::setRecepient(SocketRecipient * recep)
{
	m_pRecepient = recep;
}

std::vector<std::shared_ptr<SocketWorker>> WorkerManager::getWorkers() const
{
	return m_workers;
}

void WorkerManager::startServer()
{
	m_acceptor.setWorkerManager(this);
	m_acceptor.Create(PORT);
	m_acceptor.Listen();
	m_isListening = true;
}

void WorkerManager::startServer(SocketRecipient* recep)
{
	m_pRecepient = recep;
	startServer();
}

void WorkerManager::stopServer()
{
	closeAll();
	m_isListening = false;
}

void WorkerManager::closeAll()
{
	m_acceptor.Close();
	for (auto& worker : m_workers) {
		CString ipAddress;
		UINT port;
		worker->GetPeerName(ipAddress, port);
		worker->Close();
		m_pRecepient->OnClose(ipAddress, port, 0);
	}
}

void WorkerManager::OnAccept(int errorCode)
{
	auto newWorker = std::make_shared<SocketWorker>(this);
	m_acceptor.Accept(*newWorker);

	if (inspect(newWorker)) {
		m_workers.push_back(newWorker);
	}
	else {
		
	}

	Log::log("[%d]", m_workers.size());

	CString ipAddress;
	UINT Port;
	newWorker->GetPeerName(ipAddress, Port);

	assert(m_pRecepient);
	m_pRecepient->OnAccept(ipAddress, Port, errorCode);

	m_acceptor.Listen();
}

void WorkerManager::OnReceive(const CString& ipAddress, UINT port, int errorCode)
{
	auto sender = findWorkerOrNull(ipAddress, port);
	if (!sender) {
		Log::err("IP:%s, PORT:%d: 비정상적 접근: ", ipAddress, port);
	}

	CSocketFile file(&(*sender));
	CArchive ar(&file, CArchive::load);
	char buf[BUFLEN];
	ar.ReadString(buf, BUFLEN);

	assert(m_pRecepient);
	m_pRecepient->OnReceive(ipAddress, port, buf, errorCode);
}

void WorkerManager::OnClose(const CString& ipAddress, UINT port, int errorCode)
{
	bool removeSuccess = removeOrFalse(ipAddress, port);
	if (!removeSuccess) {
		Log::err("IP:%s, PORT:%d: 비정상적 접근: ", ipAddress, port);
	}

	m_pRecepient->OnClose(ipAddress, port, errorCode);
}

bool WorkerManager::isListening() const
{
	return m_isListening;
}

bool WorkerManager::inspect(std::shared_ptr<SocketWorker> target)
{
	return true;
}

std::shared_ptr<SocketWorker> WorkerManager::findWorkerOrNull(const CString & ipAddress, UINT port) const
{	
	for (auto& worker : m_workers) {
		CString ipTest;
		UINT portTest;
		worker->GetPeerName(ipTest, portTest);
		if (ipTest.Compare(ipAddress) == 0 && port == portTest) {
			return worker;
		}
	}

	return NULL;
}

bool WorkerManager::removeOrFalse(const CString & ipAddress, UINT port)
{
	std::vector<std::shared_ptr<SocketWorker>>::iterator itor;
	for (itor = m_workers.begin(); itor != m_workers.end(); ++itor) {
		CString ipTest;
		UINT portTest;
		(*itor)->GetPeerName(ipTest, portTest);
		if (ipTest.Compare(ipAddress) == 0 && port == portTest) {
			m_workers.erase(itor);
			return true;
		}
	}

	return false;
}
