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
