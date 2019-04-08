#include "stdafx.h"
#include "Worker.h"

namespace SurveyTask {
	Worker::Worker()
	{
	}


	Worker::~Worker()
	{
	}

	IdType SurveyTask::Worker::getId() const
	{
		return m_id;
	}

	void SurveyTask::Worker::setId(IdType id)
	{
		m_id = id;
	}

	CString SurveyTask::Worker::getWorkerName() const
	{
		return m_workerName;
	}

	void SurveyTask::Worker::setWorkerName(CString workerName)
	{
		m_workerName = workerName;
	}

	IdType SurveyTask::Worker::generateId() const
	{
		return 0;
	}
}