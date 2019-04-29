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
		SurveyTask::Task* getLoadedTask();

		bool startTask(UINT id);
		bool stopTask(UINT id);
		bool loadTask(UINT id);
		void appendTask(const SurveyTask::Task& task);
		bool removeTask(UINT id);

		bool setSelection(UINT id, bool select=true);

		void registerSurvey(SurveyTask::Survey survey, UINT taskId=0);
		const std::vector<SurveyTask::Survey>& getSurveys(UINT taskId=0);

	private:
		std::vector<SurveyTask::Task> m_tasks;
		UINT m_selectedId;
		UINT m_startedTaskId = 0;
		UINT m_loadedTaskId = 0;

	protected:
		TaskManager();
		static TaskManager* m_pThis;

	public:
		static TaskManager* GetInstance();
		void ReleaseInstance();		
	};
}