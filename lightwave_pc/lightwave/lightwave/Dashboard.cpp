// Dashboard_.cpp: 구현 파일
//

#include "stdafx.h"
#include "lightwave.h"
#include "Dashboard.h"
#include "ServerWorker.h"
#include "afxdialogex.h"
#include "Server.h"
#include "Common.h"
#include <iostream>

// Dashboard_ 대화 상자

IMPLEMENT_DYNAMIC(Dashboard, CDialogEx)

Dashboard::Dashboard(const Server* listenServer, CWnd* pParent)
	: CDialogEx(IDD_DASHBOARD_DIALOG, pParent), m_server(listenServer)
{
	m_brushBackground.CreateSolidBrush(RGB(50,50,50));
}

BOOL Dashboard::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	const ClientList& workers = m_server->getWorkers();
	const int workerCount = workers.size();
	setClientListEntries(workers);
	
	
	return 0;
}

void Dashboard::updateClientList(const Server* serverParam)
{
	assert(serverParam == m_server);
	auto workers = serverParam->getWorkers();
	setClientListEntries(workers);
}

Dashboard::~Dashboard()
{
}

void Dashboard::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CLIENT_LIST, ClientIPList);
}

void Dashboard::setClientListEntries(const ClientList& clientList)
{
	ClientIPList.ResetContent();
	int clientCount = clientList.size();
	for (int i = 0; i < clientCount; ++i) {
		ClientIPList.AddString(&clientList[i]->getIPAddressW()[0]);
	}	
}


BEGIN_MESSAGE_MAP(Dashboard, CDialogEx)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// Dashboard_ 메시지 처리기


BOOL Dashboard::OnEraseBkgnd(CDC* pDC)
{
	/*CRect rcClip;
	pDC->GetClipBox(rcClip);
	pDC->FillRect(rcClip, &m_brushBackground);
	return TRUE;*/
	return CDialogEx::OnEraseBkgnd(pDC);
}
