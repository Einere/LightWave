#pragma once

#include "json/json.h"

namespace Service
{
	class SocketWorker;
	/* ��û�� ���� 4���� + ������ ��û Invalid*/
	enum Method {
		Get = 0,
		Post = 1,
		Put = 2,
		Delete = 3,
		Invalid = 4,
	};

	enum Status {
		OK = 2, // ���� ��û
		BAD_REQUEST = 4, // �� ���� ��û (��: ��û ���� �Ҹ���)
	};

	const std::map<std::string, Method> methodMap = { {"GET", Get}, {"POST", Post}, {"PUT", Put}, {"DELETE", Delete} };
	const std::string NO_RESPONSE = "";

	Json::Value Error(std::string msg);
	Json::Value Success(Json::Value payload);
	Json::Value NoResponse();
	bool IsNoResponse(Json::Value v);
	bool IsAuthorized(const SocketWorker& worker);

	typedef bool authRequirements[4];

	/* ������ ��û�� ó���ϴ� ���� Monkey Ŭ�������� �������̽� ����*/
	class Monkey
	{
	public:
		Monkey(const std::string subject);
		~Monkey();

		virtual Json::Value Handle(Json::Value props, SocketWorker& socketWorker);
		const std::string GetSubject();

		virtual Json::Value DoGet(Json::Value props, SocketWorker& socketWorker) { return Json::nullValue; };
		virtual Json::Value DoPost(Json::Value props, SocketWorker& socketWorker) { return Json::nullValue; };
		virtual Json::Value DoPut(Json::Value props, SocketWorker& socketWorker) { return Json::nullValue; };
		virtual Json::Value DoDelete(Json::Value props, SocketWorker& socketWorker) { return Json::nullValue; };

	protected:
		std::string m_subject;
		authRequirements m_authList = { true, true, true, true };

		Method GetMethodOrInvalid(Json::Value root);
	};

	/* 
	���Ͽ��� �о���� ��û ������ �޾� ������ ����� ���� �Ѵ�.
	���� ��û�� ó���� �� �ִ� Monkey���� ���� ������ �����Ͽ� ���� �����Ѵ�.
	*/
	class RequestResolver
	{
	public:
		RequestResolver();
		~RequestResolver();

		/* ���� ��û(json)�� ���� ������ ��ȯ */
		std::string Resolve(SocketWorker& pSocket, std::string json);

	private:
		/* ��û ó���� ����ϴ� Monkey�� */
		std::shared_ptr<Monkey> GetMonkeyOrNull(Json::Value root);
		std::shared_ptr<Monkey> GetMiddlewareOrNull(Json::Value root);
		std::vector<std::shared_ptr<Monkey>> m_monkeys;
		std::vector<std::shared_ptr<Monkey>> m_middlewares;
	};
}

