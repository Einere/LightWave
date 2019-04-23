#pragma once

#include "Survey.h"
#include <atlimage.h>

// SurveyInfoDlg 대화 상자

class SurveyInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SurveyInfoDlg)

public:
	SurveyInfoDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	SurveyInfoDlg(SurveyTask::Survey& survey, CWnd* pParent = nullptr);
	virtual ~SurveyInfoDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_SURVEY_INFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_memo;

private:
	SurveyTask::Survey m_survey;
	std::vector<CImage> m_images;
	std::vector<CStatic*> m_imageContainers;

	void destroyImageContainers();
public:
	afx_msg void OnPaint();
	afx_msg BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CString m_updatedTime;
	CString m_workerName;
};
