#include "stdafx.h"
#include "Worker.h"
#include "time.h"

Workers::Worker::Worker(IdType _id, CString _name, CString _ip, UINT _port, bool _authorized)
{
	name = _name;
	ip = _ip;
	port = _port;
	authorized = _authorized;

	// id 생성은 반드시 다른 필드 값들이 채워진 후 수행해야한다.
	id = _id != 0 ? _id : GenerateId(*this);
}

Json::Value Workers::Worker::ToJson() const
{
	Json::Value root;
	root["id"] = id;
	root["name"] = name.GetString();
	root["ip"] = ip.GetString();
	root["port"] = port;

	return root;
}

bool Workers::Worker::FromJson(Json::Value root)
{
	Json::Value idRoot = root["id"];
	Json::Value nameRoot = root["name"];
	Json::Value ipRoot = root["ip"];
	Json::Value portRoot = root["port"];

	if (idRoot.isNull()
		|| nameRoot.isNull()
		|| ipRoot.isNull()
		|| portRoot.isNull()) {
		return false;
	}

	id = idRoot.asUInt();
	name = nameRoot.asCString();
	ip = ipRoot.asCString();
	port = portRoot.asUInt();
	
	return true;
}

Workers::IdType Workers::GenerateId(const Worker& worker)
{
	const int LENGTH = 9;
	SYSTEMTIME curTime;
	GetLocalTime(&curTime);

	CString timeInStr = TimeUtil::ConvertTime2StrNumber(curTime);
	CString idInStr = "1";

	idInStr += timeInStr;
	UINT id = atoi(idInStr);

	int nameLength = worker.name.GetLength();
	for (int i = 0; i < nameLength; ++i) {
		id = 10 * id + worker.name[i];
	}

	return id;
}
