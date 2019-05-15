#include "stdafx.h"
#include "MainFrm.h"
#include "TaskWnd.h"
#include "Task.h"
#include "TaskAddDlg.h"
#include "TaskManager.h"
#include "ParcelManager.h"
#include "afxdialogex.h"
#include "resource.h"

// CTaskMngDlg ��ȭ ����

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

	m_listTask.InsertColumn(1, _T("ID"), LVCFMT_LEFT, (int)(width*0.3), 2);
	m_listTask.InsertColumn(2, _T("�۾���"), LVCFMT_LEFT, (int)(width*0.3), 2);
	m_listTask.InsertColumn(3, _T("����"), LVCFMT_LEFT, (int)(width*0.3), 2);

	std::regex reg(".*tsk$");
	std::vector<path> files;
	File::FindFile("./working-data", reg, files);
	for (auto file : files) {
		SurveyTask::Task task;
		task.Load(file.generic_string().c_str());
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
	ON_COMMAND(ID_TASK_MNG_START_TASK, &CTaskMngDlg::OnTaskMngStartTask)
	ON_NOTIFY(LVN_ITEMACTIVATE, IDC_LIST_TASK, &CTaskMngDlg::OnLvnItemActivateListTask)
	ON_BN_CLICKED(IDC_BUTTON_START_TASK, &CTaskMngDlg::OnBnClickedButtonStartTask)
END_MESSAGE_MAP()



SurveyTask::Task& CTaskMngDlg::appendTask(const SurveyTask::Task& task)
{
	auto taskManager = ProgramManager::TaskManager::GetInstance();
	taskManager->AppendTask(task);

	CString idInString;
	idInString.Format("%d", task.GetId());
	const std::vector<LPCTSTR> values = { idInString, task.GetTaskName(), task.GetLotNumber()};
	const int valueCount = values.size();

	const int itemIndex = m_listTask.GetItemCount();
	m_listTask.InsertItem(itemIndex, values[0]);

	for (int i = 1; i < valueCount; ++i) {
		m_listTask.SetItemText(itemIndex, i, values[i]);
	}

	return taskManager->GetTaskByIndex(taskManager->GetTasksCount()-1);
}

bool CTaskMngDlg::StartSelectedTask()
{
	UINT id = GetSelectedId();

	auto taskManager = ProgramManager::TaskManager::GetInstance();
	BOOL hasStarted = taskManager->StartTask(id);
	if (!hasStarted) {
		MessageBox("���� ������ �۾��� �ƴմϴ�.", "���", MB_ICONWARNING);
		return false;
	}

	SurveyTask::Task* pTask;
	pTask = taskManager->GetTaskByIdOrNull(id);

	char notice[100];
	sprintf(notice, "�۾��� ���۵Ǿ����ϴ�.\n�۾� ID: %d\n�۾� �̸�: %s", pTask->GetId(), pTask->GetTaskName().GetString());
	MessageBox(notice, "�ȳ�", MB_ICONINFORMATION);

	return true;
}

UINT CTaskMngDlg::GetSelectedId() const
{
	int mark = m_listTask.GetSelectionMark();
	if (-1 == mark) return -1;

	CString idInString = m_listTask.GetItemText(mark, 0);
	return _ttoi(idInString);
}

int CTaskMngDlg::deleteSelectedTask()
{
	UINT id = GetSelectedId();
	if (-1 == id) return 0;

	auto taskManager = ProgramManager::TaskManager::GetInstance();
	taskManager->RemoveTask(id);

	int mark = m_listTask.GetSelectionMark();
	BOOL success = m_listTask.DeleteItem(mark);
	
	if (!success) return -1;

	int nextMark = mark <= m_listTask.GetItemCount() - 1 ? mark : mark - 1;
	
	if (nextMark >= 0) {
		m_listTask.SetItemState(nextMark, LVIS_SELECTED, LVIS_SELECTED);
		m_listTask.SetSelectionMark(nextMark);
	}

	return 1;
}

void CTaskMngDlg::OnBnClickedButtonAddTask()
{
	TaskAddDlg dlg;
	if (dlg.DoModal() == IDOK) {
		auto& newTask = appendTask(dlg.getTask());
		ASSERT(newTask.Store());

		Logger::Log("�۾��� ��ϵǾ����ϴ�: [�۾���: %s\t ��ǥ����: %s]", newTask.GetTaskName(), newTask.GetLotNumber());
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
		TRACE0("��� â�� ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
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
	if (-1 == GetSelectedId()) {
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

	int index = pNMItemActivate->iItem; // Ŭ���� �������� �ε��� ����
	if (index >= 0 ) // ǥ�õ� �����۵��߿� Ŭ���� �Ʒ� �ڵ� ����
	{
		CString idInString = m_listTask.GetItemText(index, 0);
		UINT id = _ttoi(idInString);
		
		taskManager->SetSelection(id, TRUE);
	}
	else {
		taskManager->SetSelection(0, FALSE);
	}

	*pResult = 0;
}

void CTaskMngDlg::OnTaskMngDelete()
{
	deleteSelectedTask();
}

void CTaskMngDlg::OnTaskMngActive()
{
	UINT id = GetSelectedId();
	auto taskManager = ProgramManager::TaskManager::GetInstance();

	SurveyTask::Task* pTask;
	pTask = taskManager->GetTaskByIdOrNull(id);
	if (pTask == NULL) return;

	CString fileName = pTask->GetCifPath();
	if (fileName.IsEmpty()) {
		MessageBox("�ش� �۾��� ��ϵ� CIF������ �����ϴ�.", "CIF���� �ε� ����", MB_ICONERROR);
		return;
	}

	auto pManager = ProgramManager::TaskManager::GetInstance();
	pManager->LoadTask(id);
}

void CTaskMngDlg::OnTaskMngStartTask()
{
	StartSelectedTask();
}


void CTaskMngDlg::OnLvnItemActivateListTask(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	OnTaskMngActive();

	*pResult = 0;
}

void CTaskMngDlg::OnBnClickedButtonStartTask()
{
	StartSelectedTask();
}
