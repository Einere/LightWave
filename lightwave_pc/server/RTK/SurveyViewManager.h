#pragma once

#include "VeCad/cadapi.h"
#include "Task.h"

namespace ProgramManager {
	class SurveyViewManager
	{
	public:
		const std::vector<VHANDLE>& GetSurveyHandles() const;
		bool MakeSurveyPoint(SurveyTask::Survey survey, DWORD nKey, CString sExKey);
		void AppendSurveyHandle(VHANDLE h);
		void LoadSurveysFromTask(const SurveyTask::Task& task);
		void ClearAllData();
		
		bool DrawSurveyPoints();

	private:
		std::vector<VHANDLE> m_surveyHandles;



	protected:
		static SurveyViewManager* m_pThis;

	public:
		static SurveyViewManager* GetInstance();
		static void ReleaseInstance();

	protected:
		SurveyViewManager(void);
	public:
		~SurveyViewManager(void);
	};
}