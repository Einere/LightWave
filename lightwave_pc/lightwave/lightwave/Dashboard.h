#pragma once

#include "Server.h"

class Dashboard : public CDialogEx
{
	DECLARE_DYNAMIC(Dashboard)

public:
	//Dashboard(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	Dashboard(const Server* server, CWnd* pParent = nullptr);
	virtual ~Dashboard();

	BOOL OnInitDialog();
	void updateClientList(const Server* serverParam);

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DASHBOARD_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

private:
	const Server* m_server = nullptr;
	CBrush m_brushBackground;
	void setClientListEntries(const ClientList& clientList);
	
public:
	CListBox ClientIPList;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
