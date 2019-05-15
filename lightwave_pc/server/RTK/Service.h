#pragma once

#include "json/json.h"

namespace Service
{
	class SocketWorker;
	/* 요청의 종류 4가지 + 비정상 요청 Invalid*/
	enum Method {
		Get = 0,
		Post = 1,
		Put = 2,
		Delete = 3,
		Invalid = 4,
	};

	enum Status {
		OK = 2, // 정상 요청
		BAD_REQUEST = 4, // 비 정상 요청 (예: 요청 형식 불만족)
	};

	const std::map<std::string, Method> methodMap = { {"GET", Get}, {"POST", Post}, {"PUT", Put}, {"DELETE", Delete} };
	const std::string NO_RESPONSE = "";

	Json::Value Error(std::string msg);
	Json::Value Success(Json::Value payload);
	Json::Value NoResponse();
	bool IsNoResponse(Json::Value v);
	bool IsAuthorized(const SocketWorker& worker);

	typedef bool authRequirements[4];

	/* 각각의 요청을 처리하는 하위 Monkey 클래스들의 인터페이스 역할*/
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
	소켓에서 읽어들인 요청 내용을 받아 응답을 만드는 일을 한다.
	들어온 요청을 처리할 수 있는 Monkey에게 응답 생성을 위임하여 일을 수행한다.
	*/
	class RequestResolver
	{
	public:
		RequestResolver();
		~RequestResolver();

		/* 들어온 요청(json)에 대한 응답을 반환 */
		std::string Resolve(SocketWorker& pSocket, std::string json);

	private:
		/* 요청 처리를 담당하는 Monkey들 */
		std::shared_ptr<Monkey> GetMonkeyOrNull(Json::Value root);
		std::shared_ptr<Monkey> GetMiddlewareOrNull(Json::Value root);
		std::vector<std::shared_ptr<Monkey>> m_monkeys;
		std::vector<std::shared_ptr<Monkey>> m_middlewares;
	};
}

