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

	// TODO: ��û �۽����� ���� Ȯ�� (�㰡�� �۾��ڰ� �´°�?)

	return Json::Value();
}
