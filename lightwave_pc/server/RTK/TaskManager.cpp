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

	const std::vector<SurveyTask::Task>& TaskManager::GetTasks() const
	{
		return m_tasks;
	}

	SurveyTask::Task & TaskManager::GetTaskByIndex(UINT index)
	{
		return m_tasks[index];
	}

	SurveyTask::Task* TaskManager::GetTaskById(UINT id)
	{
		for (auto& task : m_tasks) {
			if (id == task.GetId()) {
				return &task;
			}
		}

		return NULL;
	}

	UINT TaskManager::GetSelectedTaskIdOrZero() const
	{
		return m_selectedId > 0 ? m_selectedId : 0;
	}

	UINT TaskManager::GetTasksCount() const
	{
		return m_tasks.size();
	}

	SurveyTask::Task* TaskManager::GetStartedTask()
	{
		if (0 == m_startedTaskId) return NULL;

		return GetTaskById(m_startedTaskId);
	}

	SurveyTask::Task * TaskManager::GetLoadedTask()
	{
		if (0 == m_loadedTaskId) return NULL;

		return GetTaskById(m_loadedTaskId);
	}

	void TaskManager::AppendTask(const SurveyTask::Task & task)
	{
		m_tasks.push_back(SurveyTask::Task(task));
	}

	bool TaskManager::RemoveTask(UINT id)
	{
		std::vector<SurveyTask::Task>::iterator itor;
		for (itor = m_tasks.begin(); itor != m_tasks.end(); ++itor) {
			if (id == itor->GetId()) {
				CString result = itor->Remove(true);
				if (result.IsEmpty()) return false;

				m_tasks.erase(itor);
				return true;
			}
		}

		return false;
	}

	bool TaskManager::SetSelection(UINT id, bool select)
	{
		if (!select) {
			m_selectedId = -1;
			return true;
		}

		SurveyTask::Task* pTask;
		pTask = GetTaskById(id);
		if (pTask == NULL) return false;

		m_selectedId = id;

		return true;
	}

	bool TaskManager::StartTask(UINT id)
	{
		SurveyTask::Task* pTask;
		pTask = GetTaskById(id);
		assert(pTask != NULL);

		if (0 != m_startedTaskId) {
			SurveyTask::Task* pTaskToBeStopped;
			pTaskToBeStopped = GetTaskById(m_startedTaskId);
			pTaskToBeStopped->Stop();
		}

		bool hasStarted = pTask->Start();
		if (!hasStarted) return NULL;

		m_startedTaskId = id;
		return true;
	}

	bool TaskManager::StopTask(UINT id)
	{
		SurveyTask::Task* pTask;
		pTask = GetTaskById(id);
		assert(pTask != NULL);

		bool hasStopped = pTask->Stop();
		if (!hasStopped) return NULL;

		assert(m_startedTaskId == id);
		m_startedTaskId = 0;
		return true;
	}

	bool TaskManager::LoadTask(UINT id)
	{
		SurveyTask::Task* pTask;
		pTask = GetTaskById(id);
		assert(pTask != NULL);

		if (id == m_loadedTaskId) {
			return false;
		}

		m_loadedTaskId = id;

		bool loadCifResult = CParcelManager::GetInstance()->LoadCif(pTask->GetCifPath());
		if (!loadCifResult) {
			return false;
		}

		SurveyViewManager::GetInstance()->LoadSurveysFromTask(*pTask);

		return true;
	}

	void TaskManager::RegisterSurvey(SurveyTask::Survey survey, UINT taskId)
	{
		if (taskId == 0) {
			taskId = m_startedTaskId;
		}

		SurveyTask::Task* task = GetTaskById(taskId);
		task->RegisterSurvey(survey);
	}

	const std::vector<SurveyTask::Survey>& TaskManager::GetSurveys(UINT taskId)
	{
		if (taskId == 0 && 0 != m_loadedTaskId) {
			taskId = m_loadedTaskId;
		}
		else if (0 == m_loadedTaskId) {
			return std::vector<SurveyTask::Survey>();
		}

		SurveyTask::Task* task = GetTaskById(taskId);
		return task->GetSurveys();
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