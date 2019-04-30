#include "stdafx.h"
#include "TestMonkey.h"

#include "MainFrm.h"

TestMonkey::TestMonkey() : Monkey("test")
{
}


TestMonkey::~TestMonkey()
{
}

Json::Value TestMonkey::DoGet(Json::Value props, SocketWorker& socketWorker)
{
	auto pMainWnd = (CMainFrame*)AfxGetMainWnd();

	CString ip;
	UINT port;
	socketWorker.GetPeerName(ip, port);
	pMainWnd->OnReceive(ip, port, props, 0);
	Json::Value root;
	root["data"] = "Success!";
	return root;
}

