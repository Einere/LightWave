#pragma once

namespace Service {
	/*
	클라이언트의 최초 연결 요청(connect)에 대한 수락(accept)만을 담당.
	성공적으로 accept되면, 해당 클라이언트의 요청을 전담 처리하는 SocketWorker를 생성하여 모든 요청 처리를 맡긴다.
	*/
	class SocketAcceptor : public CSocket
	{
	public:
		SocketAcceptor();
		~SocketAcceptor();

		virtual void OnAccept(int nErrorCode);
	};
}