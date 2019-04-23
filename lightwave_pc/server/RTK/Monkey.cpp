#include "stdafx.h"
#include "Service.h"
#include "SocketWorker.h"

namespace Service {
	Monkey::Monkey(const std::string subject)
	{
		m_subject = subject;
	}

	Monkey::~Monkey()
	{
	}

	Json::Value Monkey::handle(Json::Value props, SocketWorker& socketWorker)
	{
		Method method = getMethodOrInvalid(props);
		Json::Value result;
		switch (method) {
		case Method::Get:
			result = doGet(props, socketWorker);
			break;
		case Method::Post:
			result = doPost(props, socketWorker);
			break;
		case Method::Put:
			result = doPut(props, socketWorker);
			break;
		case Method::Delete:
			result = doDelete(props, socketWorker);
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

	Json::Value error(std::string msg)
	{
		Json::Value err;
		err["status"] = BAD_REQUEST;
		err["message"] = msg;
		return err;
	}

	Json::Value success(Json::Value payload)
	{
		payload["status"] = OK;
		return payload;
	}

	bool isAuthorized(const SocketWorker & worker)
	{
		return worker.isAuthorized();
	}
}