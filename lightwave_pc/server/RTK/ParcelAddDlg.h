#pragma once
// ParcelAddDlg 대화 상자

class Task;

class ParcelAddDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ParcelAddDlg)

public:
	ParcelAddDlg(const std::vector<Task>& tasks, CWnd* pParent = nullptr);
	virtual ~ParcelAddDlg();

	bool getSelectedTask(Task& taskOut);
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_SET_PARCEL };
#endif
private:
	const std::vector<Task>& m_tasks;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_taskList;
	CString m_selected;
	virtual afx_msg BOOL OnInitDialog();
};
