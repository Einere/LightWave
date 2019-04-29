#include "stdafx.h"
#include "SurveyViewManager.h"
#include "CadManager.h"

namespace ProgramManager {
	const std::vector<VHANDLE>& SurveyViewManager::GetSurveyHandles() const
	{
		return m_surveyHandles;
	}

	bool SurveyViewManager::MakeSurveyPoint(SurveyTask::Survey survey, DWORD nKey, CString sExKey)
	{	
		auto hDwg = CCadManager::GetInstance()->GetVDwg();
		VHANDLE hLayer = CadGetLayerByName(hDwg, survey.HasBeenSurveyed()?"100":"101");
		CadSetCurLayer(hDwg, hLayer);

		VHANDLE hEnt = CadAddCircle(hDwg, survey.GetX(), survey.GetY(), 0, 3);
		CadEntityPutFilled(hEnt, TRUE);
		m_surveyHandles.push_back(hEnt);

		return true;
	}

	void SurveyViewManager::AppendSurveyHandle(VHANDLE h)
	{
		m_surveyHandles.push_back(h);
	}

	void SurveyViewManager::LoadSurveysFromTask(const SurveyTask::Task & task)
	{
		ClearAllData();

		auto pCadManager = CCadManager::GetInstance();
		auto hDwg = CCadManager::GetInstance()->GetVDwg();

		VHANDLE hLayer100 = CadGetLayerByName(hDwg, "100");
		VHANDLE hLayer101 = CadGetLayerByName(hDwg, "101");
		if (hLayer100 == NULL) {
			bool makeLayerResult = pCadManager->MakeLayer("100", CAD_COLOR_CYAN); // 작업자가 전송한 측량 정보를 표시하기 위한 레이어
		}

		if (hLayer101 == NULL) {
			bool makeLayerResult = pCadManager->MakeLayer("101", CAD_COLOR_MAGENTA); // 작업자가 전송한 측량 정보를 표시하기 위한 레이어
		}

		auto& surveys = task.getSurveys();
		for (auto& survey : surveys) {
			MakeSurveyPoint(survey, 504, "");
		}

		VHANDLE hLayer71 = CadGetLayerByName(hDwg, "71");
		CadSetCurLayer(hDwg, hLayer71);

		CadUpdate(hDwg);
		CadRegen(hDwg);
	}

	void SurveyViewManager::ClearAllData()
	{
		/*if(m_surveyHandles.size()>0)
			CadEntityErase(m_surveyHandles[0], true);*/
		int handlesCount = m_surveyHandles.size();
		for (int i = 0; i < handlesCount; ++i) {
			CadEntityErase(m_surveyHandles[i], true);
		}
		
		m_surveyHandles.clear();
	}

	bool SurveyViewManager::DrawSurveyPoints()
	{
		// 작업자의 측량 위치 생성
		/*auto pTaskManager = TaskManager::GetInstance();
		if (pTaskManager->getLoadedTask() != NULL) {
			CadSetCurLayer(m_hDwg, hLayer100);
			UINT taskId = pTaskManager->getSelectedTaskIdOrZero();
			auto surveys = pTaskManager->getSurveys();
			for (auto& s : surveys) {
				if (!s.HasBeenSurveyed()) {
					CadLayerPutColor(hLayer100, CAD_COLOR_RED);
				}
				else {
					CadLayerPutColor(hLayer100, CAD_COLOR_CYAN);
				}

				MakeSurveyPoint(s, 504, "");
			}
		}*/
		return false;
	}

	SurveyViewManager* SurveyViewManager::m_pThis = NULL;

	SurveyViewManager * SurveyViewManager::GetInstance()
	{
		if (m_pThis == NULL)
		{
			m_pThis = new SurveyViewManager;
		}
		return m_pThis;
	}

	void SurveyViewManager::ReleaseInstance()
	{
		if (m_pThis != NULL)
		{
			delete m_pThis;
			m_pThis = NULL;
		}
	}

	SurveyViewManager::SurveyViewManager()
	{
	}


	SurveyViewManager::~SurveyViewManager()
	{
	}
}