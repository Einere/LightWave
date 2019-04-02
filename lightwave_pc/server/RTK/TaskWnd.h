#pragma once

#include "ConnectionStateDlg.h"

class Task;

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
	void appendTask(const Task& task);
	const std::vector<Task>& getTasks() const;
	std::shared_ptr<Task> getSelectedTaskOrNull() const;

public:
	afx_msg void OnBnClickedButtonAddTask();
	afx_msg void OnBnClickedButtonDeleteTask();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnInitDialog();

private:

	CListCtrl m_listTask;
	std::vector<Task> m_tasks;
};

class TaskWnd : public CDockablePane {
public:
	TaskWnd();
	~TaskWnd();

	void appendTask(const Task& task);
	const std::vector<Task>& getTasks() const;

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()

private:
	CTaskMngDlg m_dlg;
};