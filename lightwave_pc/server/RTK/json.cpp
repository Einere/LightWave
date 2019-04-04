#include "stdafx.h"
#include "json.h"

Json::Value Json::parse(std::string jsonString)
{
	Json::Reader reader;
	Json::Value json;
	bool parsingResult = reader.parse(jsonString, json);
	if (!parsingResult) return Json::nullValue;

	return json;
}

std::string Json::json2Str(Json::Value root)
{
	Json::FastWriter writer;
	std::string buf = writer.write(root);
	return buf;
}
