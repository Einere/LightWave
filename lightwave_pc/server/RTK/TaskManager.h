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
		BOOL getTaskById(UINT id, SurveyTask::Task& task_Out);
		UINT getSelectedTaskId() const;
		UINT getTasksCount() const;

		void appendTask(const SurveyTask::Task& task);

		BOOL removeTask(UINT id);

		BOOL setSelection(UINT id, BOOL select=TRUE);

	private:
		std::vector<SurveyTask::Task> m_tasks;
		UINT m_selectedId;

	protected:
		static TaskManager* m_pThis;

	public:
		static TaskManager* GetInstance();
		void ReleaseInstance();
	};
}