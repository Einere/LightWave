#pragma once

#include <json.h>
#include <string>

class JsonParser
{
public:
	
	JsonParser();
	~JsonParser();

	static Json::Value parse(std::string jsonData, Json::Value& root, bool collectComments = true);
};

