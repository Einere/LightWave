#pragma once

#include "json/json.h"

class SocketWorker;

namespace Service
{
	enum Method {
		Invalid = 0,
		Get = 1,
		Post = 2,
		Put = 3,
		Delete = 4
	};

	enum Status {
		BAD_REQUEST = 4,
	};

	const std::map<std::string, Method> methodMap = { {"GET", Get}, {"POST", Post}, {"PUT", Put}, {"DELETE", Delete} };

	class Monkey
	{
	public:
		Monkey(const std::string subject);
		~Monkey();

		Json::Value handle(Json::Value props);
		const std::string getSubject();

		virtual Json::Value doGet(Json::Value props) { return Json::nullValue;/*차후 invalid request라는 것을 알려주는 코드가 여기 들어가야함*/ }
		virtual Json::Value doPost(Json::Value props) { return Json::nullValue; }
		virtual Json::Value doPut(Json::Value props) { return Json::nullValue; }
		virtual Json::Value doDelete(Json::Value props) { return Json::nullValue; }

	protected:
		std::string m_subject;

		Method getMethodOrInvalid(Json::Value root);
		Json::Value error(std::string msg);
	};

	class RequestResolver
	{
	public:
		RequestResolver();
		~RequestResolver();

		std::string resolve(SocketWorker* pSocket, std::string json);

	private:
		std::shared_ptr<Monkey> getMonkeyOrNull(Json::Value root);
		std::vector<std::shared_ptr<Monkey>> monkeys;
	};
}

