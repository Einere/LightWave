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
		OK = 2,
		BAD_REQUEST = 4,
	};

	const std::map<std::string, Method> methodMap = { {"GET", Get}, {"POST", Post}, {"PUT", Put}, {"DELETE", Delete} };

	Json::Value error(std::string msg);
	Json::Value success(Json::Value payload);
	bool isAuthorized(const SocketWorker& worker);

	class Monkey
	{
	public:
		Monkey(const std::string subject);
		~Monkey();

		Json::Value handle(Json::Value props, SocketWorker& socketWorker);
		const std::string getSubject();

		virtual Json::Value doGet(Json::Value props, SocketWorker& socketWorker) = 0;
		virtual Json::Value doPost(Json::Value props, SocketWorker& socketWorker) = 0;
		virtual Json::Value doPut(Json::Value props, SocketWorker& socketWorker) = 0;
		virtual Json::Value doDelete(Json::Value props, SocketWorker& socketWorker) = 0;

	protected:
		std::string m_subject;

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

