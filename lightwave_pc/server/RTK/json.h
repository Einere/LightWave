#pragma once
#include "json/json.h"

namespace Json {
	Json::Value parse(std::string jsonString);
	std::string json2Str(Json::Value root);
}

