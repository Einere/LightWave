#pragma once

#include "ConnectionStateDlg.h"
#include "TaskMngDlg.h"

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
