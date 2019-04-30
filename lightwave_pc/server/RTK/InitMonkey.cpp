#include "stdafx.h"
#include "InitMOnkey.h"


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
		return Service::Error("`data` property is required.");
	}
	
	Json::Value jsonUserName = jsonData["userName"];
	if (jsonUserName.isNull()) {
		return Service::Error("`userName` property is required.");
	}
	socketWorker.SetWorkerName(jsonUserName.asCString());
	socketWorker.SetAuthorized();

	/*auto pManager = WorkerManager::GetInstance();
	auto worker = pManager->getWorkerOrNull(props["ip-address"].asCString(), props["port"].asUInt());
	if (!worker) return Service::error("Invalid Request");

	worker->setWorkerName(jsonData["userName"].asCString());
	worker->setAuthorized();*/

	return Json::Value();
}
