#pragma once

#include "Task.h"
#include "Survey.h"

namespace ProgramManager {
	class TaskManager
	{
	public:
		~TaskManager();

		/* �۾� ���� ��ü�� ���� ��ȸ �Լ��� */
		const std::vector<SurveyTask::Task>& GetTasks() const;
		SurveyTask::Task& GetTaskByIndex(UINT index);
		SurveyTask::Task* GetTaskByIdOrNull(UINT id);
		UINT GetSelectedTaskIdOrZero() const;
		UINT GetTasksCount() const;
		SurveyTask::Task* GetStartedTask();
		SurveyTask::Task* GetLoadedTask();

		/* 
		�۾� ����
		�̹� ���� ���� �۾��� ���� �� �۾��� ������ ��� ���� �۾��� �ߴܵǰ� ���ο� �۾��� ����
		*/
		bool StartTask(UINT id);
		bool StopTask(UINT id);

		/* �۾��� ��ϵ� ��������(.cif)�� ��ϵ� ������Ȳ�� �߾� ����â�� ǥ�� */
		bool LoadTask(UINT id);

		/* �۾� �߰�/���� */
		void AppendTask(const SurveyTask::Task& task);
		bool RemoveTask(UINT id);

		/* �۾� ����â���� ����ڰ� ����(�� �� Ŭ��)������ ��ŷ */
		bool SetSelection(UINT id, bool select=true);

		/* Ư�� �۾��� �������� ���� */
		void RegisterSurvey(SurveyTask::Survey survey, UINT taskId=0);
		const std::vector<SurveyTask::Survey>& GetSurveys(UINT taskId=0);

	private:
		std::vector<SurveyTask::Task> m_tasks;
		UINT m_selectedId;
		UINT m_startedTaskId = 0;
		UINT m_loadedTaskId = 0;

	/*
	���� �̱��� ����
	*/
	private:
		TaskManager();
		static TaskManager* m_pThis;

	public:
		static TaskManager* GetInstance();
		static void ReleaseInstance();		
	};
}