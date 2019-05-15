#pragma once

#include "VeCad/cadapi.h"
#include "Task.h"

namespace ProgramManager {
	class SurveyViewManager
	{
	public:
		/* ���� �����ִ� ������ ������ �ڵ� �迭 ��ȯ */
		const std::vector<VHANDLE>& GetSurveyHandles() const;

		/*
		ȭ��� ������ ǥ��
		�� �Ķ���� 'nKey'�� 'sExKey'���� �ӽ������� 0�� ''�� �����Ѵ�.
		*/
		bool MakeSurveyPoint(SurveyTask::Survey survey, DWORD nKey, CString sExKey);

		/* �۾� ������ ����ִ� Task ��ü�� ��� �������� ȭ�鿡 ǥ�� */
		void LoadSurveysFromTask(const SurveyTask::Task& task);

		/* ���� ǥ�õ� ��� ������ ���� */
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