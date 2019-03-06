#pragma once

class Task;
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
	afx_msg void onCreate();

	CString getTaskName() const;
	CString getTaskDesc() const;
	CString getFileName() const;
	CString getLotNumber() const;
	Task getTask() const;

private:
	CEdit m_editTitle;
	CEdit m_editDesc;
	CEdit m_editFileName;
	CButton m_btnSelectFile;
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
