#include "stdafx.h"
#include "MainFrm.h"
#include "TaskWnd.h"
#include "Task.h"
#include "TaskAddDlg.h"
#include "FileManager.h"
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

	CRect listRect;
	m_listTask.GetWindowRect(&listRect);
	const int width = listRect.Width();

	m_listTask.InsertColumn(1, _T("ID"), LVCFMT_LEFT, width*0.5, 2);
	m_listTask.InsertColumn(2, _T("작업명"), LVCFMT_LEFT, width*0.5, 2);
	m_listTask.InsertColumn(3, _T("지번"), LVCFMT_LEFT, width*0.5, 2);

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
END_MESSAGE_MAP()



SurveyTask::Task& CTaskMngDlg::appendTask(const SurveyTask::Task& task)
{
	m_tasks.push_back(SurveyTask::Task(task));

	CString idInString;
	idInString.Format("%d", task.getId());
	const std::vector<LPCTSTR> values = { idInString, task.getTaskName(), task.getLotNumber()};
	const int valueCount = values.size();

	const int itemIndex = m_listTask.GetItemCount();
	m_listTask.InsertItem(itemIndex, values[0]);

	for (int i = 1; i < valueCount; ++i) {
		m_listTask.SetItemText(itemIndex, i, values[i]);
	}

	return m_tasks[m_tasks.size() - 1];
}

const std::vector<SurveyTask::Task>& CTaskMngDlg::getTasks() const
{
	return m_tasks;
}

int CTaskMngDlg::deleteSelectedTask()
{
	UINT index = getSelectedTaskIndex();
	assert(-1 != index);

	m_tasks[index].remove();
	m_tasks.erase(m_tasks.begin() + index);

	int mark = m_listTask.GetSelectionMark();
	BOOL success = m_listTask.DeleteItem(mark);
	
	if (!success) return -1;
	return 1;
}

BOOL CTaskMngDlg::findTaskById(UINT id, SurveyTask::Task& task_Out) const
{
	for (auto task : m_tasks) {
		if (id == task.getId()) {
			task_Out = task;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CTaskMngDlg::getSelectedTask(SurveyTask::Task & task_Out) const
{
	UINT taskIndex = getSelectedTaskIndex();
	if (-1 == taskIndex) return FALSE;

	task_Out = m_tasks[taskIndex];
	return TRUE;
}

UINT CTaskMngDlg::getSelectedTaskIndex() const
{
	int mark = m_listTask.GetSelectionMark();
	CString idInString = m_listTask.GetItemText(mark, 0);

	UINT id = _ttoi(idInString);
	UINT tasksCount = m_tasks.size();

	for (int i = 0; i < tasksCount; ++i) {
		if (id == m_tasks[i].getId()) return i;
	}

	return -1;
}

void CTaskMngDlg::OnBnClickedButtonAddTask()
{
	TaskAddDlg dlg;
	if (dlg.DoModal() == IDOK) {
		auto& newTask = appendTask(dlg.getTask());
		assert(newTask.save());

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

void TaskWnd::appendTask(const SurveyTask::Task& task)
{
	m_dlg.appendTask(task);
}

const std::vector<SurveyTask::Task>& TaskWnd::getTasks() const
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
	if (-1 == getSelectedTaskIndex()) {
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
	
	getSelectedTaskIndex();

	*pResult = 0;
}

void CTaskMngDlg::OnTaskMngDelete()
{
	deleteSelectedTask();
}

void CTaskMngDlg::OnTaskMngActive()
{
	SurveyTask::Task task;
	BOOL exist = getSelectedTask(task);
	if (!exist) return;

	CString fileName = task.getFileName();
	if (fileName.IsEmpty()) {
		MessageBox("해당 작업에 등록된 CIF파일이 없습니다.", "CIF파일 로드 에러", MB_ICONERROR);
		return;
	}

	auto manager = ProgramManager::CParcelManager::GetInstance();
	manager->LoadCif(task.getFileName());
}
