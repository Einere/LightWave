// TaskAddDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "TaskAddDlg.h"
#include "Task.h"
#include "afxdialogex.h"


// TaskAddDlg 대화 상자
IMPLEMENT_DYNAMIC(TaskAddDlg, CDialogEx)

TaskAddDlg::TaskAddDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_TASK_ADD, pParent)
	, m_taskName(_T(""))
	, m_taskDesc(_T(""))
	, m_fileName(_T(""))
	, m_lotNumber(_T(""))
{
}

TaskAddDlg::~TaskAddDlg()
{
}

void TaskAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_EDIT_TASK_TITLE, m_editTitle);
	//DDX_Control(pDX, IDC_EDIT_TASK_DESC, m_editDesc);
	
	//DDX_Control(pDX, IDC_BUTTON_CHOOSE_FILE, m_btnSelectFile);
	DDX_Control(pDX, IDC_EDIT_FILE_NAME, m_editFileName);
	DDX_Control(pDX, IDOK, m_btnAdd);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Text(pDX, IDC_EDIT_TASK_TITLE, m_taskName);
	DDX_Text(pDX, IDC_EDIT_TASK_DESC, m_taskDesc);
	DDX_Text(pDX, IDC_EDIT_FILE_NAME, m_fileName);
	DDX_Text(pDX, IDC_EDIT_LOT_NUMBER, m_lotNumber);
}

BEGIN_MESSAGE_MAP(TaskAddDlg, CDialogEx)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON_CHOOSE_FILE, &TaskAddDlg::OnBnClickedButtonChooseFile)
	ON_BN_CLICKED(IDOK, &TaskAddDlg::OnBnClickedOk)
END_MESSAGE_MAP()

// TaskAddDlg 메시지 처리기


void TaskAddDlg::OnBnClickedButtonChooseFile()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CFileDialog cifOpenDlg(true, "cif", "*.cif", 6UL, "Cif File(*.cif)|*.cif|All File(*.*)|*.*||", this);
	if (IDOK == cifOpenDlg.DoModal()) {
		m_editFileName.SetWindowTextA(cifOpenDlg.GetPathName());
	}
}

SurveyTask::Task TaskAddDlg::getTask() const
{
	/*************
	name,
	lotNumber,
	fileName,
	description,
	*************/
	SurveyTask::Task task;
	task.SetTaskName(m_taskName);
	task.SetTaskDesc(m_taskDesc);
	task.SetLotNumber(m_lotNumber);
	task.SetCifPath(m_fileName);

	return task;
}

void TaskAddDlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
}
