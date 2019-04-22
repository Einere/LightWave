#include "stdafx.h"
#include "MainFrm.h"
#include "TaskWnd.h"
#include "Task.h"
#include "TaskAddDlg.h"
#include "FileManager.h"
#include "TaskManager.h"
#include "ParcelManager.h"
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

	m_listTask.SetExtendedStyle(m_listTask.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	CRect listRect;
	m_listTask.GetWindowRect(&listRect);
	const int width = listRect.Width();

	m_listTask.InsertColumn(1, _T("ID"), LVCFMT_LEFT, width*0.3, 2);
	m_listTask.InsertColumn(2, _T("작업명"), LVCFMT_LEFT, width*0.3, 2);
	m_listTask.InsertColumn(3, _T("지번"), LVCFMT_LEFT, width*0.3, 2);

	std::regex reg(".*tsk$");
	std::vector<path> files;
	File::findFile("./working-data", reg, files);
	for (auto file : files) {
		SurveyTask::Task task;
		task.load(file.generic_string().c_str());
		appendTask(task);
	}

	return TRUE;
}

BEGIN_MESSAGE_MAP(CTaskMngDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADD_TASK, &CTaskMngDlg::OnBnClickedButtonAddTask)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_TASK, &CTaskMngDlg::OnBnClickedButtonDeleteTask)
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_NOTIFY(NM_CLICK, IDC_LIST_TASK, &CTaskMngDlg::OnNMClickListTask)
	ON_COMMAND(ID_TASK_MNG_DELETE, &CTaskMngDlg::OnTaskMngDelete)
	ON_COMMAND(ID_TASK_MNG_ACTIVE, &CTaskMngDlg::OnTaskMngActive)
	ON_COMMAND(ID_TASK_MNG_TOGGLE_STATE, &CTaskMngDlg::OnTaskMngToggleState)
	ON_NOTIFY(LVN_ITEMACTIVATE, IDC_LIST_TASK, &CTaskMngDlg::OnLvnItemActivateListTask)
END_MESSAGE_MAP()



SurveyTask::Task& CTaskMngDlg::appendTask(const SurveyTask::Task& task)
{
	auto taskManager = ProgramManager::TaskManager::GetInstance();
	taskManager->appendTask(task);

	CString idInString;
	idInString.Format("%d", task.getId());
	const std::vector<LPCTSTR> values = { idInString, task.getTaskName(), task.getLotNumber()};
	const int valueCount = values.size();

	const int itemIndex = m_listTask.GetItemCount();
	m_listTask.InsertItem(itemIndex, values[0]);

	for (int i = 1; i < valueCount; ++i) {
		m_listTask.SetItemText(itemIndex, i, values[i]);
	}

	return taskManager->getTaskByIndex(taskManager->getTasksCount()-1);
}

UINT CTaskMngDlg::getSelectedId() const
{
	int mark = m_listTask.GetSelectionMark();
	if (-1 == mark) return -1;

	CString idInString = m_listTask.GetItemText(mark, 0);
	return _ttoi(idInString);
}

int CTaskMngDlg::deleteSelectedTask()
{
	UINT id = getSelectedId();
	if (-1 == id) return 0;

	auto taskManager = ProgramManager::TaskManager::GetInstance();
	taskManager->removeTask(id);

	int mark = m_listTask.GetSelectionMark();
	BOOL success = m_listTask.DeleteItem(mark);
	
	if (!success) return -1;
	return 1;
}

//BOOL CTaskMngDlg::getSelectedTask(SurveyTask::Task & task_Out) const
//{
//	UINT taskIndex = getSelectedTaskIndex();
//	if (-1 == taskIndex) return FALSE;
//
//	task_Out = m_tasks[taskIndex];
//	return TRUE;
//}
//
//UINT CTaskMngDlg::getSelectedTaskIndex() const
//{
//	int mark = m_listTask.GetSelectionMark();
//	CString idInString = m_listTask.GetItemText(mark, 0);
//
//	UINT id = _ttoi(idInString);
//	UINT tasksCount = m_tasks.size();
//
//	for (int i = 0; i < tasksCount; ++i) {
//		if (id == m_tasks[i].getId()) return i;
//	}
//
//	return -1;
//}

void CTaskMngDlg::OnBnClickedButtonAddTask()
{
	TaskAddDlg dlg;
	if (dlg.DoModal() == IDOK) {
		auto& newTask = appendTask(dlg.getTask());
		assert(newTask.store());

		Log::log("작업이 등록되었습니다: [작업명: %s\t 대표지번: %s]", newTask.getTaskName(), newTask.getLotNumber());
	}
}

void CTaskMngDlg::OnBnClickedButtonDeleteTask()
{
	deleteSelectedTask();
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

BEGIN_MESSAGE_MAP(TaskWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()



int TaskWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_dlg.Create(IDD_DLG_TASK_MANAGEMENT, this))
	{
		TRACE0("출력 창을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	m_dlg.ShowWindow(SW_SHOW);

	return 0;
}

void TaskWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	m_dlg.SetWindowPos(NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER); 
	/*m_wndTaskList.SetWindowPos(NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);*/
}


void CTaskMngDlg::OnContextMenu(CWnd * pWnd, CPoint point)
{
	if (-1 == getSelectedId()) {
		CDialogEx::OnContextMenu(pWnd, point);
		return;
	}

	CMenu popup;
	CMenu* pMenu;

	popup.LoadMenu(IDR_TASK_MNG_POPUP);
	pMenu = popup.GetSubMenu(0);

	pMenu->TrackPopupMenu(TPM_LEFTALIGN || TPM_RIGHTBUTTON, point.x, point.y, this);
}

void CTaskMngDlg::OnNMClickListTask(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	auto taskManager = ProgramManager::TaskManager::GetInstance();

	int index = pNMItemActivate->iItem; // 클릭한 아이템의 인덱스 얻어옴
	if (index >= 0 ) // 표시된 아이템들중에 클릭시 아래 코드 실행
	{
		CString idInString = m_listTask.GetItemText(index, 0);
		UINT id = _ttoi(idInString);
		
		taskManager->setSelection(id, TRUE);
	}
	else {
		taskManager->setSelection(0, FALSE);
	}

	*pResult = 0;
}

void CTaskMngDlg::OnTaskMngDelete()
{
	deleteSelectedTask();
}

void CTaskMngDlg::OnTaskMngActive()
{
	UINT id = getSelectedId();
	auto taskManager = ProgramManager::TaskManager::GetInstance();

	SurveyTask::Task* pTask;
	pTask = taskManager->getTaskById(id);
	if (pTask == NULL) return;

	CString fileName = pTask->getCifPath();
	if (fileName.IsEmpty()) {
		MessageBox("해당 작업에 등록된 CIF파일이 없습니다.", "CIF파일 로드 에러", MB_ICONERROR);
		return;
	}

	auto manager = ProgramManager::CParcelManager::GetInstance();
	manager->LoadCif(pTask->getCifPath());
}

void CTaskMngDlg::OnTaskMngToggleState()
{
	UINT id = getSelectedId();
	auto taskManager = ProgramManager::TaskManager::GetInstance();

	BOOL hasStarted = taskManager->startTask(id);
	if (!hasStarted) {
		MessageBox("시작 가능한 작업이 아닙니다.", "경고", MB_ICONWARNING);
		return;
	}
	
	SurveyTask::Task* pTask;
	pTask = taskManager->getTaskById(id);
	assert(pTask != NULL);

	char notice[100];
	sprintf(notice, "작업이 시작되었습니다.\n작업 ID: %d\n작업 이름: %s", pTask->getId(), pTask->getTaskName());
	MessageBox(notice, "안내", MB_ICONINFORMATION);
}


void CTaskMngDlg::OnLvnItemActivateListTask(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	OnTaskMngActive();

	*pResult = 0;
}

