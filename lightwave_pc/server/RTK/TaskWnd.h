#pragma once

#include "ConnectionStateDlg.h"

class Task;

// CTaskMngDlg 대화 상자
class CTaskMngDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTaskMngDlg)

public:
	CTaskMngDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CTaskMngDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_TASK_MANAGEMENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	BOOL appendTask(std::shared_ptr<Task> pTask);

public:
	afx_msg void OnBnClickedButtonAddTask();
	afx_msg void OnBnClickedButtonDeleteTask();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnInitDialog();

private:
	CListCtrl m_listTask;
};


class TaskList : public CListBox {
public:
	TaskList();
	~TaskList();

	afx_msg void OnViewTask();

	DECLARE_MESSAGE_MAP()
};

class TaskWnd : public CDockablePane {
public:
	TaskWnd();
	~TaskWnd();

	void appendTask(std::shared_ptr<Task> pTask);

protected:
	TaskList m_wndTaskList;

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()

private:
	CTaskMngDlg m_dlg;
};
