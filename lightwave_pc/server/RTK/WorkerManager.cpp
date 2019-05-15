#include "stdafx.h"
#include "WorkerManager.h"

WorkerManager::WorkerManager() {

}

WorkerManager::~WorkerManager()
{
}

const std::vector<std::shared_ptr<Service::SocketWorker>>& WorkerManager::GetWorkers()
{
	return m_workers;
}

void WorkerManager::StartServer()
{
	/*const int PORT_STR_LENGTH = 5;
	char portInStr[PORT_STR_LENGTH];
	m_port = GetEnvironmentVariable("PORT", portInStr, PORT_STR_LENGTH) ? atoi(portInStr) : 8080;*/

	m_acceptor.Create(m_port);
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

	if (m_nextPort != 0) m_port = m_nextPort;
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
	m_workers.clear();
}

void WorkerManager::AppendWorker(std::shared_ptr<Service::SocketWorker> pNewWorker)
{
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
}

void WorkerManager::DeleteWorker(const CString& targetIpaddr, UINT targetPort)
{
	auto itor = m_workers.begin();
	for (auto itor = m_workers.begin(); itor != m_workers.end(); ++itor) {
		CString ipAddr;
		UINT port;
		(*itor)->GetPeerName(ipAddr, port);
		if (targetIpaddr == ipAddr && port == targetPort) {
			(*itor)->Close();
			m_workers.erase(itor);
			Notify();
			break;
		}
	}
}

void WorkerManager::DeleteWorker(CString name)
{
	auto itor = m_workers.begin();
	for (auto itor = m_workers.begin(); itor != m_workers.end(); ++itor) {
		if (0 == (*itor)->GetWorkerName().Compare(name)) {
			m_workers.erase(itor);
			(*itor)->Close();
			Notify();
			break;
		}
	}
}

bool WorkerManager::IsListening() const
{
	return m_isListening;
}

bool WorkerManager::Inspect(std::shared_ptr<Service::SocketWorker> target)
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

void WorkerManager::SetPort(UINT port)
{
	if (IsListening()) {
		m_nextPort = port;
		return;
	}

	m_port = port;
}

UINT WorkerManager::GetPortNow() const
{
	return m_port;
}

UINT WorkerManager::GetPort() const
{
	return (m_nextPort ? m_nextPort : m_port);
}

void WorkerManager::GetIpAddrs(std::vector<CString>& ips) const
{
#pragma comment(lib, "Iphlpapi.lib")
	IP_ADAPTER_ADDRESSES*       adapters = NULL;
	IP_ADAPTER_ADDRESSES*       adapter = NULL;
	IP_ADAPTER_UNICAST_ADDRESS* adr = NULL;
	ULONG                       adapter_size = 0;
	ULONG                       err = 0;
	SOCKADDR_IN*                sockaddr = NULL;

	err = ::GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_SKIP_ANYCAST | GAA_FLAG_SKIP_MULTICAST | GAA_FLAG_SKIP_DNS_SERVER | GAA_FLAG_SKIP_FRIENDLY_NAME, NULL, NULL, &adapter_size);
	adapters = (IP_ADAPTER_ADDRESSES*)malloc(adapter_size);
	err = ::GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_SKIP_ANYCAST | GAA_FLAG_SKIP_MULTICAST | GAA_FLAG_SKIP_DNS_SERVER | GAA_FLAG_SKIP_FRIENDLY_NAME, NULL, adapters, &adapter_size);

	for (adapter = adapters; NULL != adapter; adapter = adapter->Next)
	{
		if (adapter->IfType == IF_TYPE_SOFTWARE_LOOPBACK) continue; // Skip Loopback
		if (adapter->OperStatus != IfOperStatusUp) continue;            // Live connection only  

		for (adr = adapter->FirstUnicastAddress; adr != NULL; adr = adr->Next)
		{
			sockaddr = (SOCKADDR_IN*)(adr->Address.lpSockaddr);
			char    ipstr[INET6_ADDRSTRLEN] = { 0 };
			inet_ntop(AF_INET, &(sockaddr->sin_addr), ipstr, INET_ADDRSTRLEN);
			if (strcmp(ipstr, "0.0.0.0") != 0) ips.push_back(ipstr);
		}
	}

	free(adapters);
	adapters = NULL;
}

void WorkerManager::GetIpAddrAndPort(CString& ip, UINT& port) const
{
	std::vector<CString> ips;
	GetIpAddrs(ips);
	ip = ips[ips.size() - 1];
	port = m_port;
}

void WorkerManager::SetSocketStatePane(StatePane * pStatePane)
{
	m_pStatePane = pStatePane;
}

std::shared_ptr<Service::SocketWorker> WorkerManager::GetWorkerOrNull(CString name) const
{
	for (auto& worker : m_workers) {
		if (0 == worker->GetWorkerName().Compare(name)) {
			return worker;
		}
	}

	return NULL;
}

std::shared_ptr<Service::SocketWorker> WorkerManager::GetWorkerOrNull(const CString & ipAddress, UINT port) const
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