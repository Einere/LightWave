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

		switch (method) {
		case Method::Get:
			return doGet(props);
			break;
		case Method::Post:
			return doPost(props);
			break;
		case Method::Put:
			return doPut(props);
			break;
		case Method::Delete:
			return doDelete(props);
			break;
		case Method::Invalid:
			// 비 정상적인 입력임을 반환해야함
			break;
		default:
			assert(false);
		}
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
		Json::Value suc;
		suc["status"] = OK;
		suc["message"] = payload;
		return suc;
	}
}