#include "stdafx.h"
#include "TaskManager.h"
#include "ParcelManager.h"
#include "SurveyViewManager.h"


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
		if (0 == m_startedTaskId) return NULL;

		return getTaskById(m_startedTaskId);
	}

	SurveyTask::Task * TaskManager::getLoadedTask()
	{
		if (0 == m_loadedTaskId) return NULL;

		return getTaskById(m_loadedTaskId);
	}

	void TaskManager::appendTask(const SurveyTask::Task & task)
	{
		m_tasks.push_back(SurveyTask::Task(task));
	}

	bool TaskManager::removeTask(UINT id)
	{
		std::vector<SurveyTask::Task>::iterator itor;
		for (itor = m_tasks.begin(); itor != m_tasks.end(); ++itor) {
			if (id == itor->getId()) {
				CString result = itor->remove(true);
				if (result.IsEmpty()) return false;

				m_tasks.erase(itor);
				return true;
			}
		}

		return false;
	}

	bool TaskManager::setSelection(UINT id, bool select)
	{
		if (!select) {
			m_selectedId = -1;
			return true;
		}

		SurveyTask::Task* pTask;
		pTask = getTaskById(id);
		if (pTask == NULL) return false;

		m_selectedId = id;

		return true;
	}

	bool TaskManager::startTask(UINT id)
	{
		SurveyTask::Task* pTask;
		pTask = getTaskById(id);
		assert(pTask != NULL);

		if (0 != m_startedTaskId) {
			SurveyTask::Task* pTaskToBeStopped;
			pTaskToBeStopped = getTaskById(m_startedTaskId);
			pTaskToBeStopped->stop();
		}

		bool hasStarted = pTask->start();
		if (!hasStarted) return NULL;

		m_startedTaskId = id;
		return true;
	}

	bool TaskManager::stopTask(UINT id)
	{
		SurveyTask::Task* pTask;
		pTask = getTaskById(id);
		assert(pTask != NULL);

		bool hasStopped = pTask->stop();
		if (!hasStopped) return NULL;

		assert(m_startedTaskId == id);
		m_startedTaskId = 0;
		return true;
	}

	bool TaskManager::loadTask(UINT id)
	{
		SurveyTask::Task* pTask;
		pTask = getTaskById(id);
		assert(pTask != NULL);

		if (id == m_loadedTaskId) {
			return false;
		}

		m_loadedTaskId = id;

		bool loadCifResult = CParcelManager::GetInstance()->LoadCif(pTask->getCifPath());
		if (!loadCifResult) {
			return false;
		}

		SurveyViewManager::GetInstance()->LoadSurveysFromTask(*pTask);

		return true;
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
		if (taskId == 0 && 0 != m_loadedTaskId) {
			taskId = m_loadedTaskId;
		}
		else if (0 == m_loadedTaskId) {
			return std::vector<SurveyTask::Survey>();
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