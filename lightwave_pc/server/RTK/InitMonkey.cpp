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
			return Service::Error("`data` 필드 존재하지 않음.");
		}

		Json::Value jsonUserName = jsonData["userName"];
		if (jsonUserName.isNull() || jsonUserName.asCString() == "") {
			return Service::Error("`userName` 필드 존재하지 않음.");
		}
		socketWorker.SetWorkerName(TextEncoding::UTF82mulBCString(jsonUserName.asCString()));
		socketWorker.SetAuthorized();

		return Json::Value();
	}
}