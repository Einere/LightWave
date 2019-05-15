#pragma once

#include "Service.h"
#include "Worker.h"

namespace Service {
	/*
	����� �ϳ��� Ŭ���̾�Ʈ���� ��û/������ ���
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
		Ŭ���̾�Ʈ ������ ������ ������ ��� �� �Լ��� ȣ���Ͽ� ��Ȳ â�� �ݿ�
		��: Ŭ���̾�Ʈ�� �۾��� �̸� ���
		*/
		void NotifyUpdate() const;

		/* size�� �� ���� �� ���� ��û�� ó������ �ʰ� �б⸸ �� */
		void beginBlob(int size);
		void endBlob();

		bool isEndOfRequest() const;

	private:
		RequestResolver m_requestResolver;

		/* ������ ���� ���� ��û �����͸� ���� */
		std::string readIn();
		std::string m_data;
		int m_blobSize = 0;

		Workers::Worker m_worker;
		int GetJsonSize(std::string stringContainingKeyOfSize);
	};
}