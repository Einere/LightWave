// ParcelAddDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "ParcelAddDlg.h"
#include "Task.h"
#include "afxdialogex.h"


// ParcelAddDlg 대화 상자

IMPLEMENT_DYNAMIC(ParcelAddDlg, CDialogEx)

ParcelAddDlg::ParcelAddDlg(const std::vector<SurveyTask::Task>& tasks, CWnd* pParent)
	: CDialogEx(IDD_DLG_SET_PARCEL, pParent), m_tasks(tasks)
{
		
}

ParcelAddDlg::~ParcelAddDlg()
{
}

bool ParcelAddDlg::GetSelectedTask(SurveyTask::Task& taskOut)
{
	int taskSize = m_tasks.size();
	for (int i = 0; i < taskSize; ++i) {
		const bool isSame = (std::strcmp(m_tasks.at(i).GetTaskName(), m_selected) == 0);
		if (isSame) {
			taskOut = m_tasks.at(i);
			return true;
		}
	}

	return false;
}

void ParcelAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_TASK, m_taskList);

	int nSel = m_taskList.GetCurSel();
	if (nSel != LB_ERR)
	{
		CString taskName;
		m_taskList.GetText(nSel, taskName);
		m_selected = taskName;
	}
}

BOOL ParcelAddDlg::OnInitDialog()
{
	const bool result = CDialogEx::OnInitDialog();
	if (!result) return result;

	for (auto t : m_tasks) {
		Logger::Log("%s",t.GetTaskName());
		m_taskList.AddString(t.GetTaskName());
	}

	return TRUE;
}


BEGIN_MESSAGE_MAP(ParcelAddDlg, CDialogEx)
	ON_WM_CREATE()
END_MESSAGE_MAP()

