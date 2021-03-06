#pragma once

#include "Task.h"
// TaskAddDlg 대화 상자

class TaskAddDlg : public CDialogEx
{
	DECLARE_DYNAMIC(TaskAddDlg)

public:
	TaskAddDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~TaskAddDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_TASK_ADD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonChooseFile();

	SurveyTask::Task getTask() const;

private:
	CEdit m_editFileName;
	CButton m_btnAdd;
	CButton m_btnCancel;
public:
	
private:
	CString m_taskName;
	CString m_taskDesc;
	CString m_fileName;
	CString m_lotNumber;
public:
	afx_msg void OnBnClickedOk();
};
