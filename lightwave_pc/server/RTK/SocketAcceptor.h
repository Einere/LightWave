#pragma once

namespace Service {
	/*
	Ŭ���̾�Ʈ�� ���� ���� ��û(connect)�� ���� ����(accept)���� ���.
	���������� accept�Ǹ�, �ش� Ŭ���̾�Ʈ�� ��û�� ���� ó���ϴ� SocketWorker�� �����Ͽ� ��� ��û ó���� �ñ��.
	*/
	class SocketAcceptor : public CSocket
	{
	public:
		SocketAcceptor();
		~SocketAcceptor();

		virtual void OnAccept(int nErrorCode);
	};
}