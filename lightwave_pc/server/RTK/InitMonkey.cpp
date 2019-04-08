#include "stdafx.h"
#include "InitMOnkey.h"


InitMonkey::InitMonkey() : Monkey("start")
{
}


InitMonkey::~InitMonkey()
{
}

Json::Value InitMonkey::doPost(Json::Value props)
{
	Json::Value jsonData = props["data"];
	
	// TODO: 요청 송신자의 권한 확인 (허가된 작업자가 맞는가?)

	return Json::nullValue;
}
