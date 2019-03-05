
// MainFrm.h : CMainFrame 클래스의 인터페이스
//

#pragma once

#include "StatePane.h"
#include "TaskWnd.h"
#include "SocketRecipient.h"
#include "WorkerManager.h"
#include "FileManager.h"

class Task;
class TaskAddDlg;
class CViewHMoveDlg;
class CViewVMoveDlg;
class CViewSkyDlg;
class CGPSSNRGraphDlg;
class ConnectionStateDlg;

// 기본 Frame이다. 메뉴 이벤트들을 여기서 처리 하게 될것이다.
class CMainFrame : public CFrameWndEx, public SocketRecipient
{
public:

protected: // serialization에서만 만들어집니다.
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 특성입니다.
private:
	WorkerManager m_workerManager;
	FileManager m_fileManager;

// 작업입니다.
public:
	void addTask(Task task);

// 재정의입니다.
public:

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// 구현입니다.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 컨트롤 모음이 포함된 멤버입니다.
	CMFCMenuBar			m_wndMenuBar;
	CMFCToolBar			m_wndToolBar;
//	CMFCStatusBar		m_wndStatusBar;
	//CLogWnd				lout;
	CMFCToolBarImages	m_UserImages;
	CMFCToolBar			m_tbCadDraw; 
	CMFCToolBar			m_tbCadZoom;
	StatePane			m_wndStatePane;
	TaskWnd				m_wndTask;
	ConnectionStateDlg*	m_pStateDlg = NULL;

public:
	void updateStateDlg();
	bool isServerListening() const;

// 생성된 메시지 맵 함수
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
public:
	afx_msg void OnVecadOpen();
//	afx_msg void OnVecadOpenlayerdlg();
	afx_msg void OnDrawPoint();
	afx_msg void OnDrawLine();
	afx_msg void OnLoadCif();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg long OnCommunication(WPARAM wParam, LPARAM lParam);
	afx_msg void OnParentNotify(UINT message, LPARAM lParam);


public:

	int m_OldBuffLen;
	int m_NewBuffLen;
	int m_OldBuffLen_EN;
	int m_NewBuffLen_EN;

	afx_msg void OnConnectMachine();

	// #########################################################
	// 
	int GetNowOpenMainMenuIndex( int nIndex );
	// 
	// #########################################################
	void AddLog( CString sLog );
	afx_msg void OnOption();
	afx_msg void OnZoomExtent();
	afx_msg void OnZoomIn();
	afx_msg void OnZoomOut();
	afx_msg void OnMoveNowposition();
	afx_msg void OnZoomWindow();
	afx_msg void OnMovePan();
	afx_msg void OnLayerOpencontroller();
	afx_msg void OnDrawCircle();
	afx_msg void OnDrawRectangle();
	afx_msg void OnDrawPolyline();
	afx_msg void OnDrawPolygon();
	afx_msg void OnDrawText();
	afx_msg void OnViewGpssnrgraph();
	afx_msg void OnViewskygraph();
	afx_msg void OnViewdopgraph();
	afx_msg void OnViewhmovegraph();
	afx_msg void OnViewvmovegraph();
	afx_msg void OnDestroy();
	afx_msg void OnExportSvy();

	CViewHMoveDlg *m_pHMoveDlg;
	CViewVMoveDlg *m_pVMoveDlg;
	CViewSkyDlg *m_pSkyDlg;
	CGPSSNRGraphDlg *m_pSNRDlg;
	afx_msg void OnServerStart();
	afx_msg void OnServerStop();
	afx_msg void OnUpdateServerStop(CCmdUI *pCmdUI);
	afx_msg void showStateDlg();
	afx_msg void OnShowLog();
	afx_msg void OnAddTask();

public:
	virtual void OnAccept(const CString& ipAddress, UINT port, int errorCode);
	virtual void OnReceive(const CString& ipAddress, UINT port, const CString& msg, int errorCode);
	virtual void OnClose(const CString& ipAddress, UINT port, int errorCode);
};