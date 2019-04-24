#pragma once

#include "json/json.h"

class SocketWorker;

namespace Service
{
	enum Method {
		Get = 0,
		Post = 1,
		Put = 2,
		Delete = 3,
		Invalid = 4,
	};

	enum Status {
		OK = 2,
		BAD_REQUEST = 4,
	};

	const std::map<std::string, Method> methodMap = { {"GET", Get}, {"POST", Post}, {"PUT", Put}, {"DELETE", Delete} };

	Json::Value error(std::string msg);
	Json::Value success(Json::Value payload);
	bool isAuthorized(const SocketWorker& worker);

	typedef bool authRequirements[4];

	class Monkey
	{
	public:
		Monkey(const std::string subject);
		~Monkey();

		Json::Value handle(Json::Value props, SocketWorker& socketWorker);
		const std::string getSubject();

		virtual Json::Value doGet(Json::Value props, SocketWorker& socketWorker) { return Json::nullValue; };
		virtual Json::Value doPost(Json::Value props, SocketWorker& socketWorker) { return Json::nullValue; };
		virtual Json::Value doPut(Json::Value props, SocketWorker& socketWorker) { return Json::nullValue; };
		virtual Json::Value doDelete(Json::Value props, SocketWorker& socketWorker) { return Json::nullValue; };

	protected:
		std::string m_subject;
		authRequirements m_authList = { true, true, true, true };

		Method getMethodOrInvalid(Json::Value root);
	};

	class RequestResolver
	{
	public:
		RequestResolver();
		~RequestResolver();

		std::string resolve(SocketWorker& pSocket, std::string json);

	private:
		std::shared_ptr<Monkey> getMonkeyOrNull(Json::Value root);
		std::vector<std::shared_ptr<Monkey>> monkeys;
	};


}

