#pragma once

#include "ConnectionStateDlg.h"
#include "Task.h"

class CTaskMngDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTaskMngDlg)

public:
	CTaskMngDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CTaskMngDlg();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_TASK_MANAGEMENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	SurveyTask::Task& appendTask(const SurveyTask::Task& task);

public:
	afx_msg void OnBnClickedButtonAddTask();
	afx_msg void OnBnClickedButtonDeleteTask();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnInitDialog();

private:
	UINT getSelectedId() const;
	int deleteSelectedTask();

	CListCtrl m_listTask;

public:
	afx_msg void OnContextMenu(CWnd *pWnd, CPoint point);
	afx_msg void OnNMClickListTask(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTaskMngDelete();
	afx_msg void OnTaskMngActive();
	afx_msg void OnLvnItemActivateListTask(NMHDR *pNMHDR, LRESULT *pResult);
};

class TaskWnd : public CDockablePane {
public:
	TaskWnd();
	~TaskWnd();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()

private:
	CTaskMngDlg m_dlg;
};