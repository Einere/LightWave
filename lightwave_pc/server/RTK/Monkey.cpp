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

	Json::Value Monkey::Handle(Json::Value props, SocketWorker& socketWorker)
	{
		Method method = GetMethodOrInvalid(props);
		if (method == Method::Invalid) {
			return Error("요청 메소드가 명시되지 않았습니다. 큰 데이터를 보내는 경우라면 데이터 사이즈를 명시하는 요청이 선행되어야 합니다.");
		}

		if (m_authList[method]) {
			if (!socketWorker.IsAuthorized()) {
				return Error("허가되지 않은 요청입니다. 서버에 사용자가 등록되어있지 않을 수 있습니다.");
			}
		}

		Json::Value result;
		switch (method) {
		case Method::Get:
			result = DoGet(props, socketWorker);
			break;
		case Method::Post:
			result = DoPost(props, socketWorker);
			break;
		case Method::Put:
			result = DoPut(props, socketWorker);
			break;
		case Method::Delete:
			result = DoDelete(props, socketWorker);
			break;
		case Method::Invalid:
			result = Error("Invalid Method: Send with one in these methods ['GET', 'POST', 'PUT', 'DELETE']");
			break;
		default:
			ASSERT(false);
		}

		if (result["status"].isNull()) {
			result = Success(result);
		}

		return result;
	}

	const std::string Monkey::GetSubject()
	{
		return m_subject;
	}

	Method Monkey::GetMethodOrInvalid(Json::Value root)
	{
		const std::string methodInString = root["method"].asString();
		if (methodInString == "" || methodMap.find(methodInString) == methodMap.end()) {
			return Method::Invalid;
		}

		return methodMap.at(methodInString);
	}

	Json::Value Error(std::string msg)
	{
		Json::Value err;
		err["status"] = BAD_REQUEST;
		err["message"] = msg;
		return err;
	}

	Json::Value Success(Json::Value payload)
	{
		payload["status"] = OK;
		return payload;
	}

	Json::Value NoResponse()
	{
		Json::Value ret;
		ret["noResponse"] = true;
		return ret;
	}

	bool IsNoResponse(Json::Value v)
	{
		return (v["noResponse"]!=Json::nullValue && v["noResponse"].asBool());
	}

	bool IsAuthorized(const SocketWorker & worker)
	{
		return worker.IsAuthorized();
	}
}