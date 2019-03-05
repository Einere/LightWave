#include "stdafx.h"
#include "TaskWnd.h"
#include "Task.h"
#include "resource.h"

TaskWnd::TaskWnd()
{
}


TaskWnd::~TaskWnd()
{
}

void TaskWnd::appendTask(std::shared_ptr<Task> pTask)
{
	BOOL result = m_dlg.appendTask(pTask);
	assert(result);
}

BEGIN_MESSAGE_MAP(TaskWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()



int TaskWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	/*CRect rectDummy;
	rectDummy.SetRectEmpty();*/

	//const DWORD dwStyle = LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;

	if (!m_dlg.Create(IDD_DLG_TASK_MANAGEMENT, this))
	{
		TRACE0("출력 창을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	m_dlg.ShowWindow(SW_SHOW);

	//if (!m_wndTaskList.Create(dwStyle, rectDummy, this, 1))
	//{
	//	TRACE0("출력 창을 만들지 못했습니다.\n");
	//	return -1;      // 만들지 못했습니다.
	//}

	return 0;
}

void TaskWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	m_dlg.SetWindowPos(NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER); 
	/*m_wndTaskList.SetWindowPos(NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);*/
}

TaskList::TaskList()
{
}

TaskList::~TaskList()
{
}

BEGIN_MESSAGE_MAP(TaskList, CListBox)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_VIEW_TASKWND, OnViewTask)
	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()

void TaskList::OnViewTask()
{
	CDockablePane* pParentBar = DYNAMIC_DOWNCAST(CDockablePane, GetOwner());
	CMDIFrameWndEx* pMainFrame = DYNAMIC_DOWNCAST(CMDIFrameWndEx, GetTopLevelFrame());

	if (pMainFrame != NULL && pParentBar != NULL)
	{
		pMainFrame->SetFocus();
		pMainFrame->ShowPane(pParentBar, FALSE, FALSE, FALSE);
		pMainFrame->RecalcLayout();

	}
}