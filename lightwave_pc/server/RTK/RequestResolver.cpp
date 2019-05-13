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
		// ��û���� ����� �츮�� ��Ű���� �̰����� �ʱ�ȭ�մϴ�.
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
			return Json::json2Str(Error("��û ������ �ùٸ� json ���¿��� �մϴ�."));
		}


		std::shared_ptr<Monkey> monkey = GetMiddlewareOrNull(props);
		if (!monkey) {
			monkey = GetMonkeyOrNull(props);
		}

		Json::Value result;
		if (!monkey) {
			result = Error("��û�� ó���� �� �ִ� ������ ����� �������� �ʽ��ϴ�.");
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
			// ��û�� �� ��(subject)�� ��õǾ����� ����.
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
			// ��û�� �� ��(subject)�� ��õǾ����� ����.
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