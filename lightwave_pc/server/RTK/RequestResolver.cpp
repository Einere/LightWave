#include "stdafx.h"
#include <map>

#include "SocketWorker.h"
#include "Service.h"

#include "InitMonkey.h"
#include "TaskMonkey.h"
#include "ParcelMonkey.h"
#include "SurveyMonkey.h"
#include "TestMonkey.h"
#include "LengthMiddleware.h"

#include "json.h"

#include "TextEncoding.h"

#include <atlstr.h>

namespace Service {
	RequestResolver::RequestResolver()
	{
		// 요청들을 담당할 우리의 몽키들을 이곳에서 초기화합니다.
		m_monkeys.push_back(std::make_shared<InitMonkey>());
		m_monkeys.push_back(std::make_shared<TaskMonkey>());
		m_monkeys.push_back(std::make_shared<ParcelMonkey>());
		m_monkeys.push_back(std::make_shared<SurveyMonkey>());
		m_monkeys.push_back(std::make_shared<TestMonkey>());

		m_middlewares.push_back(std::make_shared<LengthMiddleware>());
	}


	RequestResolver::~RequestResolver()
	{
	}

	std::string RequestResolver::Resolve(SocketWorker& socket, std::string json)
	{
		Json::Value props = Json::parse(json);
		if (props == Json::nullValue) {
			return Json::json2Str(Error("요청 형식이 올바른 json 형태여야 합니다."));
		}


		std::shared_ptr<Monkey> monkey = GetMiddlewareOrNull(props);
		if (!monkey) {
			monkey = GetMonkeyOrNull(props);
		}

		Json::Value result;
		if (!monkey) {
			result = Error("요청을 처리할 수 있는 적절한 모듈이 존재하지 않습니다.");
		}
		else {
			result = monkey->Handle(props, socket);
		}


		return (isNoResponse(result)) ? "" : Json::json2Str(result).c_str();
	}

	std::shared_ptr<Monkey> RequestResolver::GetMonkeyOrNull(Json::Value root)
	{
		const std::string subject = root["subject"].asString();
		if (subject == "") {
			// 요청에 할 일(subject)이 명시되어있지 않음.
			return nullptr;
		}

		for (auto pMonkey : m_monkeys) {
			if (pMonkey->GetSubject().compare(subject) == 0) {
				return pMonkey;
			}
		}
		return nullptr;
	}

	std::shared_ptr<Monkey> RequestResolver::GetMiddlewareOrNull(Json::Value root)
	{
		const std::string subject = root["subject"].asString();
		if (subject == "") {
			// 요청에 할 일(subject)이 명시되어있지 않음.
			return nullptr;
		}

		for (auto pMiddleware : m_middlewares) {
			if (pMiddleware->GetSubject().compare(subject) == 0) {
				return pMiddleware;
			}
		}
		return nullptr;
	}

}