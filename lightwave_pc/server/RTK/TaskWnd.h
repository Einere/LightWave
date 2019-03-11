#pragma once

#include "ConnectionStateDlg.h"

class Task;

// CTaskMngDlg ��ȭ ����
class CTaskMngDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTaskMngDlg)

public:
	CTaskMngDlg(CWnd* pParent = nullptr);   // ǥ�� �������Դϴ�.
	virtual ~CTaskMngDlg();

	// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_TASK_MANAGEMENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
