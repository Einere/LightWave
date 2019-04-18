#include "stdafx.h"
#include "Service.h"

namespace Service {
	Monkey::Monkey(const std::string subject)
	{
		m_subject = subject;
	}

	Monkey::~Monkey()
	{
	}

	Json::Value Monkey::handle(Json::Value props)
	{
		Method method = getMethodOrInvalid(props);
		Json::Value result;
		switch (method) {
		case Method::Get:
			result = doGet(props);
			break;
		case Method::Post:
			result = doPost(props);
			break;
		case Method::Put:
			result = doPut(props);
			break;
		case Method::Delete:
			result = doDelete(props);
			break;
		case Method::Invalid:
			result = error("Invalid Method: Send with one in these methods ['GET', 'POST', 'PUT', 'DELETE']");
			break;
		default:
			assert(false);
		}

		if (result["status"].isNull()) {
			result = success(result);
		}

		return result;
	}

	const std::string Monkey::getSubject()
	{
		return m_subject;
	}

	Method Monkey::getMethodOrInvalid(Json::Value root)
	{
		const std::string methodInString = root["method"].asString();
		if (methodInString == "" || methodMap.find(methodInString) == methodMap.end()) {
			return Method::Invalid;
		}

		return methodMap.at(methodInString);
	}

	Json::Value Monkey::error(std::string msg)
	{
		Json::Value err;
		err["status"] = BAD_REQUEST;
		err["message"] = msg;
		return err;
	}

	Json::Value Monkey::success(Json::Value payload)
	{
		payload["status"] = OK;
		return payload;
	}
}