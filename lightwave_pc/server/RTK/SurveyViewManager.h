#pragma once

#include "VeCad/cadapi.h"
#include "Task.h"

namespace ProgramManager {
	class SurveyViewManager
	{
	public:
		/* 현재 열려있는 지도의 측량점 핸들 배열 반환 */
		const std::vector<VHANDLE>& GetSurveyHandles() const;

		/*
		화면상에 측량점 표시
		두 파라미터 'nKey'와 'sExKey'에는 임시적으로 0과 ''를 전달한다.
		*/
		bool MakeSurveyPoint(SurveyTask::Survey survey, DWORD nKey, CString sExKey);

		/* 작업 정보를 담고있는 Task 객체에 담긴 측량점을 화면에 표시 */
		void LoadSurveysFromTask(const SurveyTask::Task& task);

		/* 현재 표시된 모든 측량점 제거 */
		void ClearAllData();

	private:
		std::vector<VHANDLE> m_surveyHandles;
		double m_radius = 5;

	public: 
		~SurveyViewManager(void);
		static SurveyViewManager* GetInstance();
		static void ReleaseInstance();

	private:
		SurveyViewManager(void);
		static SurveyViewManager* m_pThis;
	};
}