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

	BOOL TaskManager::getTaskById(UINT id, SurveyTask::Task& task_Out) const
	{
		for (auto& task : m_tasks) {
			if (id == task.getId()) {
				task_Out = task;
				return TRUE;
			}
		}

		return FALSE;
	}

	UINT TaskManager::getSelectedTaskId() const
	{
		return m_selectedId;
	}

	UINT TaskManager::getTasksCount() const
	{
		return m_tasks.size();
	}

	BOOL TaskManager::getStartedTask(SurveyTask::Task& task_Out) const
	{
		if (-1==m_startedTaskId) return FALSE;

		getTaskById(m_startedTaskId, task_Out);
		return TRUE;
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

		SurveyTask::Task task;
		BOOL exist = getTaskById(id, task);
		if (!exist) return FALSE;

		m_selectedId = id;
		
		return TRUE;
	}

	BOOL TaskManager::startTask(UINT id)
	{
		SurveyTask::Task task;
		BOOL exist = getTaskById(id, task);
		assert(exist);

		if (-1 != m_startedTaskId) {
			SurveyTask::Task taskToBeStopped;
			getTaskById(m_startedTaskId, taskToBeStopped);
			taskToBeStopped.stop();
		}

		BOOL hasStarted = task.start();
		if (!hasStarted) return NULL;

		m_startedTaskId = id;
		return TRUE;
	}

	BOOL TaskManager::stopTask(UINT id)
	{
		SurveyTask::Task task;
		BOOL exist = getTaskById(id, task);
		assert(exist);

		BOOL hasStopped = task.stop();
		if (!hasStopped) return NULL;

		assert(m_startedTaskId == id);
		m_startedTaskId = -1;
		return TRUE;
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