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

namespace Service {
	RequestResolver::RequestResolver()
	{
		// 요청들을 담당할 우리의 몽키들을 이곳에서 초기화합니다.
		monkeys.push_back(std::make_shared<InitMonkey>());
		monkeys.push_back(std::make_shared<TaskMonkey>());
		monkeys.push_back(std::make_shared<ParcelMonkey>());
		monkeys.push_back(std::make_shared<SurveyMonkey>());
		monkeys.push_back(std::make_shared<TestMonkey>());
	}


	RequestResolver::~RequestResolver()
	{
	}

	std::string RequestResolver::resolve(SocketWorker* pSocket, std::string json)
	{
		Json::Value props = Json::parse(json);
		if (props==Json::nullValue) {
			return Json::json2Str(error("요청 형식이 올바른 json 형태여야 합니다."));
		}

		std::shared_ptr<Monkey> monkey = getMonkeyOrNull(props);

		CString ipAddr; UINT port;
		pSocket->GetPeerName(ipAddr, port);

		props["ip-address"] = (LPCTSTR)ipAddr;
		props["port"] = port;
		Json::Value result = monkey->handle(props);

		return Json::json2Str(result) + '\n';
	}

	std::shared_ptr<Monkey> RequestResolver::getMonkeyOrNull(Json::Value root)
	{
		const std::string subject = root["subject"].asString();
		if (subject == "") {
			// 요청에 할 일(subject)이 명시되어있지 않음.
			return nullptr;
		}

		for (auto pMonkey : monkeys) {
			if (pMonkey->getSubject().compare(subject) == 0) {
				return pMonkey;
			}
		}
		return nullptr;
	}
	
}