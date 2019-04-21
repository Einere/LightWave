#include "stdafx.h"
#include "TaskManager.h"


namespace ProgramManager {
	TaskManager::TaskManager()
	{
	}

	TaskManager::~TaskManager()
	{
	}

	const std::vector<SurveyTask::Task>& TaskManager::getTasks() const
	{
		return m_tasks;
	}

	SurveyTask::Task & TaskManager::getTaskByIndex(UINT index)
	{
		return m_tasks[index];
	}

	SurveyTask::Task* TaskManager::getTaskById(UINT id) 
	{
		for (auto& task : m_tasks) {
			if (id == task.getId()) {
				return &task;
			}
		}

		return NULL;
	}

	UINT TaskManager::getSelectedTaskIdOrZero() const
	{
		return m_selectedId > 0 ? m_selectedId : 0;
	}

	UINT TaskManager::getTasksCount() const
	{
		return m_tasks.size();
	}

	SurveyTask::Task* TaskManager::getStartedTask()
	{
		if (-1==m_startedTaskId) return NULL;

		return getTaskById(m_startedTaskId);
	}

	void TaskManager::appendTask(const SurveyTask::Task & task)
	{
		m_tasks.push_back(SurveyTask::Task(task));
	}

	BOOL TaskManager::removeTask(UINT id)
	{
		std::vector<SurveyTask::Task>::iterator itor;
		for (itor = m_tasks.begin(); itor != m_tasks.end(); ++itor) {
			if (id == itor->getId()) {
				BOOL removed = itor->remove(TRUE);
				if (!removed) return FALSE;

				m_tasks.erase(itor);
				return TRUE;
			}
		}

		return FALSE;
	}

	BOOL TaskManager::setSelection(UINT id, BOOL select)
	{
		if (!select) {
			m_selectedId = -1;
			return TRUE;
		}

		SurveyTask::Task* pTask;
		pTask = getTaskById(id);
		if (pTask == NULL) return FALSE;

		m_selectedId = id;
		
		return TRUE;
	}

	BOOL TaskManager::startTask(UINT id)
	{
		SurveyTask::Task* pTask;
		pTask = getTaskById(id);
		assert(pTask != NULL);

		if (-1 != m_startedTaskId) {
			SurveyTask::Task* pTaskToBeStopped;
			pTaskToBeStopped = getTaskById(m_startedTaskId);
			pTaskToBeStopped->stop();
		}

		BOOL hasStarted = pTask->start();
		if (!hasStarted) return NULL;

		m_startedTaskId = id;
		return TRUE;
	}

	BOOL TaskManager::stopTask(UINT id)
	{
		SurveyTask::Task* pTask;
		pTask = getTaskById(id);
		assert(pTask!=NULL);

		BOOL hasStopped = pTask->stop();
		if (!hasStopped) return NULL;

		assert(m_startedTaskId == id);
		m_startedTaskId = -1;
		return TRUE;
	}

	void TaskManager::registerSurvey(SurveyTask::Survey survey, UINT taskId)
	{
		if (taskId == 0) {
			taskId = m_startedTaskId;
		}


		SurveyTask::Task* task = getTaskById(taskId);
		task->registerSurvey(survey);
	}

	const std::vector<SurveyTask::Survey>& TaskManager::getSurveys(UINT taskId)
	{
		if (taskId == 0) {
			taskId = m_startedTaskId;
		}

		SurveyTask::Task* task = getTaskById(taskId);
		return task->getSurveys();
	}

	TaskManager* TaskManager::m_pThis = NULL;

	TaskManager * TaskManager::GetInstance()
	{
		if (m_pThis == NULL)
		{
			m_pThis = new TaskManager();
		}
		return m_pThis;
	}

	void TaskManager::ReleaseInstance()
	{
		if (m_pThis != NULL)
		{
			delete m_pThis;
			m_pThis = NULL;
		}
	}
}