#include "stdafx.h"
#include "StatePane.h"


StatePane::StatePane()
{
}


StatePane::~StatePane()
{
}

BEGIN_MESSAGE_MAP(StatePane, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()



int StatePane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	const DWORD dwStyle = LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;

	if (!m_stateDlg.Create(IDD_DLG_CONNECTION_STATE, this)) {
		TRACE0("��� â�� ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}
	m_stateDlg.ShowWindow(SW_SHOW);

	return 0;
}

void StatePane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	m_stateDlg.SetWindowPos(NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	//m_wndTaskList.SetWindowPos(NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void StatePane::update(bool isListening, const std::vector<std::shared_ptr<SocketWorker>> workers)
{
	m_stateDlg.update(isListening, workers);
}
