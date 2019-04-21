#include "stdafx.h"
#include "InitMOnkey.h"


InitMonkey::InitMonkey() : Monkey("meta")
{
}


InitMonkey::~InitMonkey()
{
}

Json::Value InitMonkey::doPost(Json::Value props)
{
	Json::Value jsonData = props["data"];
	
	auto pManager = WorkerManager::GetInstance();
	auto worker = pManager->getWorkerOrNull(props["ip-address"].asCString(), props["port"].asUInt());
	if (!worker) return Service::error("Invalid Request");

	worker->setWorkerName(jsonData["userName"].asCString());

	// TODO: 요청 송신자의 권한 확인 (허가된 작업자가 맞는가?)

	return Json::Value();
}
