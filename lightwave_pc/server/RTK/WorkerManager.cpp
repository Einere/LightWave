#include "stdafx.h"
#include "WorkerManager.h"
#include "SocketWorker.h"
#include "SocketRecipient.h"


//WorkerManager::WorkerManager(SocketRecipient* recep)
//	:m_acceptor()
//{
//	m_pRecepient = recep;
//}

WorkerManager::WorkerManager() {

}

WorkerManager::~WorkerManager()
{
}

//const SocketRecipient* WorkerManager::getRecepient() const
//{
//	return m_pRecepient;
//}
//
//void WorkerManager::setRecepient(SocketRecipient * recep)
//{
//	m_pRecepient = recep;
//}

const std::vector<std::shared_ptr<SocketWorker>>& WorkerManager::GetWorkers()
{
	return m_workers;
}

void WorkerManager::StartServer()
{
	m_acceptor.Create(PORT);
	m_acceptor.Listen();
	m_isListening = true;
}

//void WorkerManager::startServer(SocketRecipient* recep)
//{
//	m_pRecepient = recep;
//	startServer();
//}

void WorkerManager::StopServer()
{
	CloseAll();
	m_isListening = false;
}

void WorkerManager::CloseAll()
{
	m_acceptor.Close();
	for (auto& worker : m_workers) {
		CString ipAddress;
		UINT port;
		worker->GetPeerName(ipAddress, port);
		worker->Close();
		//m_pRecepient->OnClose(ipAddress, port, 0);
	}
}

void WorkerManager::OnAccept(std::shared_ptr<SocketWorker> pNewWorker)
{
	/*auto newWorker = std::make_shared<SocketWorker>(this);
	m_acceptor.Accept(*newWorker);*/

	if (Inspect(pNewWorker)) {
		m_workers.push_back(pNewWorker);
	}
	else {
		
	}

	Logger::Log("[%d번 째 워커]", m_workers.size());

	CString ipAddress;
	UINT port;
	pNewWorker->GetPeerName(ipAddress, port);

	Notify();
	/*assert(m_pRecepient);
	m_pRecepient->OnAccept(ipAddress, port, 0);*/
	//m_pRecepient->OnAccept(pNewWorker->getIpAddress(), pNewWorker->getPort(), 0);
}

void WorkerManager::OnReceive(SocketWorker * pSocketWorker, std::string json, int errorCode)
{
	/* 이 함수는 임시 함수로 사용하지 말 것*/
	assert(true);

	CString ipAddress;
	UINT port;
	pSocketWorker->GetPeerName(ipAddress, port);

	/*assert(m_pRecepient);
	m_pRecepient->OnReceive(ipAddress, port, json, errorCode);*/
}

void WorkerManager::OnClose(const CString& ipAddress, UINT port, int errorCode)
{
	/* 이 함수는 임시 함수로 사용하지 말 것*/
	assert(true);

	bool removeSuccess = RemoveOrFalse(ipAddress, port);
	if (!removeSuccess) {
		Logger::Err("IP:%s, PORT:%d: 비정상적 접근: ", ipAddress, port);
	}

	//m_pRecepient->OnClose(ipAddress, port, errorCode);
}

bool WorkerManager::IsListening() const
{
	return m_isListening;
}

bool WorkerManager::Inspect(std::shared_ptr<SocketWorker> target)
{
	return true;
}

void WorkerManager::Update()
{
	Notify();
}

void WorkerManager::Notify()
{
	if (m_pStatePane != NULL) {
		m_pStatePane->Update();
	}
}

void WorkerManager::SetSocketStatePane(StatePane * pStatePane)
{
	m_pStatePane = pStatePane;
}

std::shared_ptr<SocketWorker> WorkerManager::GetWorkerOrNull(const CString & ipAddress, UINT port) const
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

bool WorkerManager::RemoveOrFalse(const CString & ipAddress, UINT port)
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

WorkerManager* WorkerManager::m_pThis = NULL;

WorkerManager * WorkerManager::GetInstance()
{
	if (m_pThis == NULL)
	{
		m_pThis = new WorkerManager();
	}
	return m_pThis;
}

void WorkerManager::ReleaseInstance()
{
	if (m_pThis != NULL)
	{
		delete m_pThis;
		m_pThis = NULL;
	}
}