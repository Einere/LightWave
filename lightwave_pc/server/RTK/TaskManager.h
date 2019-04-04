#pragma once

#include "Task.h"

namespace ProgramManager {
	class TaskManager
	{
	public:
		TaskManager();
		~TaskManager();

		const std::vector<SurveyTask::Task>& getTasks() const;
		SurveyTask::Task& getTaskByIndex(UINT index);
		BOOL getTaskById(UINT id, SurveyTask::Task& task_Out) const;
		UINT getSelectedTaskId() const;
		UINT getTasksCount() const;
		BOOL getStartedTask(SurveyTask::Task& task_Out) const;

		void appendTask(const SurveyTask::Task& task);

		BOOL removeTask(UINT id);

		BOOL setSelection(UINT id, BOOL select=TRUE);

		BOOL startTask(UINT id);

		BOOL stopTask(UINT id);

	private:
		std::vector<SurveyTask::Task> m_tasks;
		UINT m_selectedId;
		UINT m_startedTaskId = -1;

	protected:
		static TaskManager* m_pThis;

	public:
		static TaskManager* GetInstance();
		void ReleaseInstance();
	};
}