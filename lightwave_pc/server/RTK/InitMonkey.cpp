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
	
	// TODO: ��û �۽����� ���� Ȯ�� (�㰡�� �۾��ڰ� �´°�?)

	return Json::nullValue;
}
