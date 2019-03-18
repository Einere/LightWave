#include "stdafx.h"
#include <map>

#include "SocketWorker.h"
#include "Service.h"

#include "ParcelMonkey.h"
#include "TestMonkey.h"

namespace Service {
	RequestResolver::RequestResolver()
	{
		// ��û���� ����� �츮�� ��Ű���� �̰����� �ʱ�ȭ�մϴ�.
		monkeys.push_back(std::make_shared<ParcelMonkey>());
		monkeys.push_back(std::make_shared<TestMonkey>());
	}


	RequestResolver::~RequestResolver()
	{
	}

	std::string RequestResolver::resolve(SocketWorker* pSocket, std::string json)
	{
		Json::Reader reader;
		Json::Value props;
		bool parsingResult = reader.parse(json, props);
		if (!parsingResult) {
			// ��û�� ���������� ������ ��ȯ
			// if ó�������� �����Ǹ� �Ʒ� assert�� ���� ��
			assert(false);
		}

		std::shared_ptr<Monkey> monkey = getMonkeyOrNull(props);

		CString ipAddr; UINT port;
		pSocket->GetPeerName(ipAddr, port);

		props["ip-address"] = (LPCTSTR)ipAddr;
		props["port"] = port;
		Json::Value result = monkey->handle(props);

		return result["message"].asString();
	}

	std::shared_ptr<Monkey> RequestResolver::getMonkeyOrNull(Json::Value root)
	{
		const std::string subject = root["subject"].asString();
		if (subject == "") {
			// ��û�� �� ��(subject)�� ���õǾ����� ����.
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