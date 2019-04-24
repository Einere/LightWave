#include "stdafx.h"
#include "Worker.h"

Workers::Worker::Worker(IdType _id, CString _name, CString _ip, UINT _port, bool _authorized)
{
	id = _id;
	name = _name;
	ip = _ip;
	port = _port;
	authorized = _authorized;
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
