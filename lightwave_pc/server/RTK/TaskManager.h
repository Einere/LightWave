#pragma once

#include "Task.h"
#include "Survey.h"

namespace ProgramManager {
	class TaskManager
	{
	public:
		~TaskManager();

		/* 작업 관련 객체에 대한 조회 함수들 */
		const std::vector<SurveyTask::Task>& GetTasks() const;
		SurveyTask::Task& GetTaskByIndex(UINT index);
		SurveyTask::Task* GetTaskByIdOrNull(UINT id);
		UINT GetSelectedTaskIdOrZero() const;
		UINT GetTasksCount() const;
		SurveyTask::Task* GetStartedTask();
		SurveyTask::Task* GetLoadedTask();

		/* 
		작업 시작
		이미 진행 중인 작업이 있을 때 작업을 시작할 경우 기존 작업은 중단되고 새로운 작업을 시작
		*/
		bool StartTask(UINT id);
		bool StopTask(UINT id);

		/* 작업에 등록된 지도파일(.cif)과 등록된 측량현황을 중앙 지도창에 표시 */
		bool LoadTask(UINT id);

		/* 작업 추가/삭제 */
		void AppendTask(const SurveyTask::Task& task);
		bool RemoveTask(UINT id);

		/* 작업 관리창에서 사용자가 선택(한 번 클릭)했음을 마킹 */
		bool SetSelection(UINT id, bool select=true);

		/* 특정 작업에 측량점을 설정 */
		void RegisterSurvey(SurveyTask::Survey survey, UINT taskId=0);
		const std::vector<SurveyTask::Survey>& GetSurveys(UINT taskId=0);

	private:
		std::vector<SurveyTask::Task> m_tasks;
		UINT m_selectedId;
		UINT m_startedTaskId = 0;
		UINT m_loadedTaskId = 0;

	/*
	이하 싱글턴 패턴
	*/
	private:
		TaskManager();
		static TaskManager* m_pThis;

	public:
		static TaskManager* GetInstance();
		static void ReleaseInstance();		
	};
}