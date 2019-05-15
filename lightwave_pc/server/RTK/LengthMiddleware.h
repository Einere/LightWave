#pragma once

#include "Service.h"
#include "SocketWorker.h"

namespace Service {
	/*
	Middleware: �Ϲ����� ��ûó�� �������� ���� ���� ������ �� �� �˻��Ͽ� Ư���� ���� ����
	���� �̵����� LengthMiddleware�� ����

	ū �����͸� ������ ���� ���� ������ ũ�� ������ �������� �ϴ� ��û�� ���
	�ش� ��û�� ���� Ŭ���̾�Ʈ�� ���Ͽ� ������ ���̸� ���� ���� ������ ��û�� ó������ �ʰ� �о����.
	*/
	class LengthMiddleware : public Service::Monkey
	{
	public:
		LengthMiddleware();
		~LengthMiddleware();

		// override
		Json::Value Handle(Json::Value props, SocketWorker& socketWorker);
	};
}
