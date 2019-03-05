// CTaskMngDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MainFrm.h"
#include "TaskMngDlg.h"
#include "Task.h";
#include "afxdialogex.h"


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



BOOL CTaskMngDlg::appendTask(std::shared_ptr<Task> pTask)
{
	const std::vector<LPCTSTR> values = { pTask->at("name"), pTask->at("lotNumber") };
	const int valueCount = values.size();

	const int itemIndex = m_listTask.GetItemCount();
	m_listTask.InsertItem(itemIndex, values[0]);

	for (int i = 1; i < valueCount; ++i) {
		m_listTask.SetItemText(itemIndex, i, values[i]);
	}

	return TRUE;
}

void CTaskMngDlg::OnBnClickedButtonAddTask()
{
	auto pMainWnd = (CMainFrame*)AfxGetMainWnd();
	pMainWnd->OnAddTask();
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
