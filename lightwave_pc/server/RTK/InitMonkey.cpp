#include "stdafx.h"
#include "InitMOnkey.h"


InitMonkey::InitMonkey() : Monkey("meta")
{
}


InitMonkey::~InitMonkey()
{
}

Json::Value InitMonkey::doPost(Json::Value props, SocketWorker& socketWorker)
{
	Json::Value jsonData = props["data"];
	
	auto pManager = WorkerManager::GetInstance();
	auto worker = pManager->getWorkerOrNull(props["ip-address"].asCString(), props["port"].asUInt());
	if (!worker) return Service::error("Invalid Request");

	worker->setWorkerName(jsonData["userName"].asCString());
	worker->setAuthorized();

	return Json::Value();
}
