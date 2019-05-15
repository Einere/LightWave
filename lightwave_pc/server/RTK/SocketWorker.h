#pragma once

#include "Service.h"
#include "Worker.h"

namespace Service {
	/*
	연결된 하나의 클라이언트와의 요청/응답을 담당
	*/
	class SocketWorker :
		public CSocket
	{
	public:
		SocketWorker();
		~SocketWorker();

		Workers::Worker GetWorker() const;

		void SetWorkerName(CString workerName);
		CString GetWorkerName();

		void SetAuthorized();
		bool IsAuthorized() const;

		virtual void OnReceive(int nErrorCode);
		virtual void OnClose(int nErrorCode);

		/*
		클라이언트 정보에 변경이 생겼을 경우 이 함수를 호출하여 현황 창에 반영
		예: 클라이언트의 작업자 이름 등록
		*/
		void NotifyUpdate() const;

		/* size를 다 받을 때 까지 요청을 처리하지 않고 읽기만 함 */
		void beginBlob(int size);
		void endBlob();

		bool isEndOfRequest() const;

	private:
		RequestResolver m_requestResolver;

		/* 소켓을 통해 들어온 요청 데이터를 읽음 */
		std::string readIn();
		std::string m_data;
		int m_blobSize = 0;

		Workers::Worker m_worker;
		int GetJsonSize(std::string stringContainingKeyOfSize);
	};
}