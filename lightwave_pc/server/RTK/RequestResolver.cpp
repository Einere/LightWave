#include "stdafx.h"
#include <map>

#include "SocketWorker.h"
#include "Service.h"

#include "InitMonkey.h"
#include "TaskMonkey.h"
#include "ParcelMonkey.h"
#include "SurveyMonkey.h"
#include "TestMonkey.h"

#include "json.h"

#include "TextEncoding.h"

#include <atlstr.h>

namespace Service {
	RequestResolver::RequestResolver()
	{
		// ��û���� ����� �츮�� ��Ű���� �̰����� �ʱ�ȭ�մϴ�.
		monkeys.push_back(std::make_shared<InitMonkey>());
		monkeys.push_back(std::make_shared<TaskMonkey>());
		monkeys.push_back(std::make_shared<ParcelMonkey>());
		monkeys.push_back(std::make_shared<SurveyMonkey>());
		monkeys.push_back(std::make_shared<TestMonkey>());
	}


	RequestResolver::~RequestResolver()
	{
	}

	std::string RequestResolver::Resolve(SocketWorker& pSocket, std::string json)
	{
		Json::Value props = Json::parse(json);
		if (props==Json::nullValue) {
			return Json::json2Str(Error("��û ������ �ùٸ� json ���¿��� �մϴ�."));
		}

		std::shared_ptr<Monkey> monkey = GetMonkeyOrNull(props);

		Json::Value result = monkey->Handle(props, pSocket);

		// TODO: UTF-8 ��ȯ �� ��ȯ
		
		

		return Json::json2Str(result).c_str();
	}

	std::shared_ptr<Monkey> RequestResolver::GetMonkeyOrNull(Json::Value root)
	{
		const std::string subject = root["subject"].asString();
		if (subject == "") {
			// ��û�� �� ��(subject)�� ��õǾ����� ����.
			return nullptr;
		}

		for (auto pMonkey : monkeys) {
			if (pMonkey->GetSubject().compare(subject) == 0) {
				return pMonkey;
			}
		}
		return nullptr;
	}
	
}