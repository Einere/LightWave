#pragma once

namespace SurveyTask {
	typedef UINT IdType;

	class Worker
	{
	public:
		Worker();
		~Worker();

		IdType getId() const;
		void setId(IdType id);

		CString getWorkerName() const;
		void setWorkerName(CString workerName);

		IdType generateId() const;

	private:
		IdType m_id;
		CString m_workerName;

	};

	
}