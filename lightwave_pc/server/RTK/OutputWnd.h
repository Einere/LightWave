
#pragma once


/////////////////////////////////////////////////////////////////////////////
// COutputList â

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// �α�â
class COutputList : public CListBox
{
// �����Դϴ�.
public:
	COutputList();

// �����Դϴ�.
public:
	virtual ~COutputList();

protected:
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnViewOutput();

	DECLARE_MESSAGE_MAP()
};




// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// �α�â�� ���������� ��ŷâ�̴�.
class CLogWnd : public CDockablePane//, public Log::Logger
{
// �����Դϴ�.
public:
	CLogWnd();

	void UpdateFonts();

// Ư���Դϴ�.
protected:
	CMFCTabCtrl	m_wndTabs;

	/*
	COutputList m_wndOutputBuild;
	COutputList m_wndOutputDebug;
	COutputList m_wndOutputFind;
	*/
	COutputList m_wndOutputLog;

protected:
	/*
	void FillBuildWindow();
	void FillDebugWindow();
	void FillFindWindow();
	*/

	void AdjustHorzScroll(CListBox& wndListBox);

// �����Դϴ�.
public:
	virtual ~CLogWnd();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()


protected:
	CString m_sLogFileName;

public:
	virtual void addLog( CString sLog );

	//deprecated
	CLogWnd& operator<<(const char* msg) {
		addLog(msg);
		return *this;
	}

	//deprecated
	CLogWnd& operator<<(double msg) {
		CString tmp;
		tmp.Format(_T("%f"), msg);
		addLog(tmp);
		return *this;
	}

protected:
	virtual void SaveLog(CString sLog);

public:
	afx_msg void OnDestroy();
};
