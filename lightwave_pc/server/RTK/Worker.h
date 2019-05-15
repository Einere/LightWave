#pragma once

#include "json.h"

namespace Workers {
	typedef UINT IdType;

	struct Worker {
		Worker(IdType _id = 0, CString _name = "", CString _ip="", UINT _port=0, bool _authorized = false);
		Json::Value ToJson() const;
		bool FromJson(Json::Value root);

		IdType id;
		CString name;
		CString ip;
		UINT port;
		bool authorized = false;
	};

	IdType GenerateId(const Worker& worker);
}