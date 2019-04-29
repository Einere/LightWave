#pragma once

#include "VeCad/cadapi.h"
#include "Task.h"

namespace ProgramManager {
	class SurveyManager
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
		static SurveyManager* m_pThis;

	public:
		static SurveyManager* GetInstance();
		static void ReleaseInstance();

	protected:
		SurveyManager(void);
	public:
		~SurveyManager(void);
	};
}