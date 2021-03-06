#pragma once

#include "Survey.h"
#include <atlimage.h>

class ImageContainer : public CStatic {
public:
	ImageContainer();
	ImageContainer(CString imagePath);
	void SetImage(CString imagePath);

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();

private:
	CImage m_image;
	CString m_imagePath;

protected:
	DECLARE_MESSAGE_MAP()
};

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
	std::vector<ImageContainer*> m_imageContainers;

	void destroyImageContainers();
public:
	afx_msg BOOL OnInitDialog();

	CString m_updatedTime;
	CString m_workerName;
	CListCtrl m_listImages;
	std::vector<SurveyTask::SurveyImage> m_images;
	afx_msg void OnLvnItemActivateListImages(NMHDR *pNMHDR, LRESULT *pResult);
};