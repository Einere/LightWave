#pragma once

#include "Task.h"
#include "Survey.h"

namespace ProgramManager {
	class TaskManager
	{
	public:
		~TaskManager();

		const std::vector<SurveyTask::Task>& getTasks() const;
		SurveyTask::Task& getTaskByIndex(UINT index);
		SurveyTask::Task* getTaskById(UINT id);
		UINT getSelectedTaskIdOrZero() const;
		UINT getTasksCount() const;
		SurveyTask::Task* getStartedTask();

		void appendTask(const SurveyTask::Task& task);

		BOOL removeTask(UINT id);

		BOOL setSelection(UINT id, BOOL select=TRUE);

		BOOL startTask(UINT id);

		BOOL stopTask(UINT id);

		void registerSurvey(SurveyTask::Survey survey, UINT taskId=0);
		const std::vector<SurveyTask::Survey>& getSurveys(UINT taskId=0);

	private:
		std::vector<SurveyTask::Task> m_tasks;
		UINT m_selectedId;
		UINT m_startedTaskId = 0;

	protected:
		TaskManager();
		static TaskManager* m_pThis;

	public:
		static TaskManager* GetInstance();
		void ReleaseInstance();		
	};
}