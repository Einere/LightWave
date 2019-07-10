#include "stdafx.h"
#include "InitMonkey.h"
#include "TextEncoding.h"

namespace Service {
	InitMonkey::InitMonkey() : Monkey("meta")
	{
		m_authList[Service::Method::Post] = false;
	}

	InitMonkey::~InitMonkey()
	{
	}

	Json::Value InitMonkey::DoPost(Json::Value props, SocketWorker& socketWorker)
	{
		Json::Value jsonData = props["data"];
		if (jsonData.isNull()) {
			return Service::Error("`data` �ʵ� �������� ����.");
		}

		Json::Value jsonUserName = jsonData["userName"];
		if (jsonUserName.isNull() || jsonUserName.asCString() == "") {
			return Service::Error("`userName` �ʵ� �������� ����.");
		}
		socketWorker.SetWorkerName(TextEncoding::UTF82mulBCString(jsonUserName.asCString()));
		socketWorker.SetAuthorized();

		return Json::Value();
	}
}