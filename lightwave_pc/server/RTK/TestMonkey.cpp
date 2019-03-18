#include "stdafx.h"
#include "TestMonkey.h"

#include "MainFrm.h"

TestMonkey::TestMonkey() : Monkey("test")
{
}


TestMonkey::~TestMonkey()
{
}

Json::Value TestMonkey::doGet(Json::Value props)
{
	auto pMainWnd = (CMainFrame*)AfxGetMainWnd();
	pMainWnd->OnReceive(props["ip-address"].asCString(), props["port"].asUInt(), props, 0);
	return Json::nullValue;
}

