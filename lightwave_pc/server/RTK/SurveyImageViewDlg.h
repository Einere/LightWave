#pragma once

#include "SurveyInfoDlg.h"

// SurveyImageViewDlg 대화 상자

class SurveyImageViewDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SurveyImageViewDlg)

public:
	SurveyImageViewDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	SurveyImageViewDlg(CString imagePath, CWnd* pParent = nullptr);
	virtual ~SurveyImageViewDlg();

	afx_msg BOOL OnInitDialog();
	afx_msg void OnPaint();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_SURVEY_IMAGE };
#endif
private:
	ImageContainer m_imageContainer;
	CImage m_image;
	CString m_imagePath;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
