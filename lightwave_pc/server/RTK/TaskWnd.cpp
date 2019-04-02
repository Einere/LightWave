#include "stdafx.h"
#include "MainFrm.h"
#include "TaskWnd.h"
#include "Task.h"
#include "TaskAddDlg.h"
#include "FileManager.h"
#include "afxdialogex.h"
#include "resource.h"

// CTaskMngDlg 대화 상자

IMPLEMENT_DYNAMIC(CTaskMngDlg, CDialogEx)

CTaskMngDlg::CTaskMngDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_TASK_MANAGEMENT, pParent)
{

}

CTaskMngDlg::~CTaskMngDlg()
{
}

void CTaskMngDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_TASK, m_listTask);
}

BOOL CTaskMngDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CRect listRect;
	m_listTask.GetWindowRect(&listRect);
	const int width = listRect.Width();

	m_listTask.InsertColumn(1, _T("작업명"), LVCFMT_LEFT, width*0.5, 2);
	m_listTask.InsertColumn(2, _T("지번"), LVCFMT_LEFT, width*0.5, 2);



	return TRUE;
}

BEGIN_MESSAGE_MAP(CTaskMngDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADD_TASK, &CTaskMngDlg::OnBnClickedButtonAddTask)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_TASK, &CTaskMngDlg::OnBnClickedButtonDeleteTask)
	ON_WM_SIZE()
END_MESSAGE_MAP()



void CTaskMngDlg::appendTask(const Task& task)
{
	m_tasks.push_back(Task(task));

	const std::vector<LPCTSTR> values = { task.getTaskName(), task.getLotNumber()};
	const int valueCount = values.size();

	const int itemIndex = m_listTask.GetItemCount();
	m_listTask.InsertItem(itemIndex, values[0]);

	for (int i = 1; i < valueCount; ++i) {
		m_listTask.SetItemText(itemIndex, i, values[i]);
	}
}

const std::vector<Task>& CTaskMngDlg::getTasks() const
{
	return m_tasks;
}

void CTaskMngDlg::OnBnClickedButtonAddTask()
{
	TaskAddDlg dlg;
	if (dlg.DoModal() == IDOK) {
		Task newTask = dlg.getTask();


		appendTask(newTask);
		assert(newTask.save());

		newTask.save();

		Log::log("작업이 등록되었습니다: [작업명: %s\t 대표지번: %s]", newTask.getTaskName(), newTask.getLotNumber());
	}
}


void CTaskMngDlg::OnBnClickedButtonDeleteTask()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CTaskMngDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	CRect rect(10, 50, cx - 10, cy - 10);


	if (m_listTask.GetSafeHwnd()) {
		m_listTask.MoveWindow(&rect);
	}
}


TaskWnd::TaskWnd()
{
}


TaskWnd::~TaskWnd()
{
}

void TaskWnd::appendTask(const Task& task)
{
	m_dlg.appendTask(task);
}

const std::vector<Task>& TaskWnd::getTasks() const
{
	return m_dlg.getTasks();
}

//std::shared_ptr<Task> TaskWnd::getSelectedTask() const
//{
//	return m_dlg.getSelectedTaskOrNull();
//}

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
