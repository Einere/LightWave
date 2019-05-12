
// MainFrm.cpp : CMainFrame Ŭ������ ����
//

#include "stdafx.h"
#include <experimental/filesystem>

#include "RTK.h"

#include "OutputWnd.h"
#include "Task.h"
#include "MainFrm.h"
#include "CadManager.h"
#include "GlobalDefine.h"
#include "ParcelManager.h"
#include "WorkerManager.h"
#include "TaskManager.h"
#include "ConnectionStateDlg.h"
#include "SocketWorker.h"
#include "SocketRecipient.h"
#include "TaskAddDlg.h"
#include "ParcelAddDlg.h"
#include "EditSurveyPointDlg.h"
#include "Survey.h"
#include "CoordConverter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace ProgramManager;
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_WM_WINDOWPOSCHANGED()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_WM_SETTINGCHANGE()
	ON_COMMAND(ID_VECAD_OPEN, &CMainFrame::OnVecadOpen)
//	ON_COMMAND(ID_VECAD_OPENLAYERDLG, &CMainFrame::OnVecadOpenlayerdlg)
	ON_COMMAND(ID_DRAW_POINT, &CMainFrame::OnDrawPoint)
	ON_COMMAND(ID_DRAW_LINE, &CMainFrame::OnDrawLine)
	ON_COMMAND(ID_LOAD_CIF, &CMainFrame::OnLoadCif)
	ON_WM_TIMER()
	ON_COMMAND(ID_CONNECT_MACHINE, &CMainFrame::OnConnectMachine)
	//ON_MESSAGE(WM_COMM_READ, OnCommunication)
	//ON_MESSAGE(WM_TCP_SOCKET_MSG, OnTcpSocketMsg)
	//ON_COMMAND(ID_Option, &CMainFrame::OnOption)
	ON_COMMAND(ID_ZOOM_EXTENT, &CMainFrame::OnZoomExtent)
	ON_COMMAND(ID_ZOOM_IN, &CMainFrame::OnZoomIn)
	ON_COMMAND(ID_ZOOM_OUT, &CMainFrame::OnZoomOut)
	ON_COMMAND(ID_MOVE_NOWPOSITION, &CMainFrame::OnMoveNowposition)
	ON_COMMAND(ID_ZOOM_WINDOW, &CMainFrame::OnZoomWindow)
	ON_COMMAND(ID_MOVE_PAN, &CMainFrame::OnMovePan)
	ON_COMMAND(ID_LAYER_OPENCONTROLLER, &CMainFrame::OnLayerOpencontroller)
	ON_COMMAND(ID_DRAW_CIRCLE, &CMainFrame::OnDrawCircle)
	ON_COMMAND(ID_DRAW_RECTANGLE, &CMainFrame::OnDrawRectangle)
	ON_COMMAND(ID_DRAW_POLYLINE, &CMainFrame::OnDrawPolyline)
	ON_COMMAND(ID_DRAW_POLYGON, &CMainFrame::OnDrawPolygon)
	ON_COMMAND(ID_DRAW_TEXT, &CMainFrame::OnDrawText)
	ON_COMMAND(ID_VIEW_GPSSNRGRAPH, &CMainFrame::OnViewGpssnrgraph)
	ON_COMMAND(ID_ViewSkyGraph, &CMainFrame::OnViewskygraph)
	ON_COMMAND(ID_ViewDopGraph, &CMainFrame::OnViewdopgraph)
	ON_COMMAND(ID_ViewHMoveGraph, &CMainFrame::OnViewhmovegraph)
	ON_COMMAND(ID_ViewVMoveGraph, &CMainFrame::OnViewvmovegraph)
	ON_WM_DESTROY()
	ON_COMMAND(ID_EXPORT_SVY, &CMainFrame::OnExportSvy)
	ON_COMMAND(ID_SERVER_START, &CMainFrame::OnServerStart)
	ON_COMMAND(ID_SERVER_STOP, &CMainFrame::OnServerStop)
	ON_UPDATE_COMMAND_UI(ID_SERVER_STOP, &CMainFrame::OnUpdateServerStop)
	ON_COMMAND(ID_SHOW_CONNECTION_STATE, &CMainFrame::ShowStateDlg)
	ON_WM_PARENTNOTIFY()
	ON_COMMAND(ID_SHOW_LOG, &CMainFrame::OnShowLog)
	ON_COMMAND(ID_ADD_TASK, &CMainFrame::OnAddTask)
	ON_COMMAND(ID_ADD_PARCEL, &CMainFrame::OnSetParcel)
	ON_COMMAND(ID_DEV_TEST, &CMainFrame::OnDevTest)
	ON_COMMAND(ID_MANAGE_SURVEY_POINTS, &CMainFrame::OnManageSurveyPoints)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ���� �� ǥ�ñ�
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/�Ҹ�

CMainFrame::CMainFrame()
{
	// TODO: ���⿡ ��� �ʱ�ȭ �ڵ带 �߰��մϴ�.
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_VS_2008);
	m_pHMoveDlg = NULL;
	m_pVMoveDlg= NULL;
	m_pSkyDlg= NULL;
	m_pSNRDlg= NULL;

	GetDockingManager()->DisableRestoreDockState(true);
}

CMainFrame::~CMainFrame() {

}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;
	// ������ ���� ���� ���־� ������ �� ��Ÿ���� �����մϴ�.
	OnApplicationLook(theApp.m_nAppLook);

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("�޴� ������ ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// �޴� ������ Ȱ��ȭ�ص� ��Ŀ���� �̵����� �ʰ� �մϴ�.
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	/*
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
	{
		TRACE0("���� ������ ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}
	*/
	

	CString strToolBarName;
	CString strCustomize;

	/*
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);
	*/
	
	/*
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	*/

//	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// CadDrawToolbar
	
	
	if (!m_tbCadDraw.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_tbCadDraw.LoadToolBar(IDR_TB_MAIN_CADDRAW) )
	{
		TRACE0("���� ������ ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}

	m_tbCadDraw.SetWindowText("CAD�׸�");

	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_tbCadDraw.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	if (!m_tbCadZoom.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_tbCadZoom.LoadToolBar(IDR_TB_CAD_ZOOM) )
	{
		TRACE0("���� ������ ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}
	m_tbCadDraw.SetWindowText("CAD��");
//	m_tbCadDraw.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	// ����� ���� ���� ���� �۾��� ����մϴ�.
	//InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	// TODO: ���� ���� �� �޴� ������ ��ŷ�� �� ���� �Ϸ��� �� �ټ� ���� �����Ͻʽÿ�.
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_tbCadDraw.EnableDocking(CBRS_ALIGN_ANY);
	m_tbCadZoom.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
//	DockPane(&m_wndToolBar);
	DockPane(&m_tbCadDraw);
	DockPane(&m_tbCadZoom);
	
	// Visual Studio 2005 ��Ÿ�� ��ŷ â ������ Ȱ��ȭ�մϴ�.
	CDockingManager::SetDockingMode(DT_SMART);
	// Visual Studio 2005 ��Ÿ�� ��ŷ â �ڵ� ���� ������ Ȱ��ȭ�մϴ�.
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// ��ŷ â�� ����ϴ�.
	if (!CreateDockingWindows())
	{
		TRACE0("��ŷ â�� ������ ���߽��ϴ�.\n");
		return -1;
	}

	Logger::lout.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&Logger::lout);

	m_wndStatePane.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndStatePane);

	m_wndTask.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndTask);

	m_wndTask.DockToWindow(&m_wndStatePane, CBRS_BOTTOM);

	// ���� ���� �� ��ŷ â �޴� �ٲٱ⸦ Ȱ��ȭ�մϴ�.
	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);
//	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// ����(<Alt> Ű�� ���� ä ����) ���� ���� ����� ������ Ȱ��ȭ�մϴ�.
	CMFCToolBar::EnableQuickCustomization();

	/*m_surveyView.setManager(CCadManager::GetInstance());
	BOOL surveyViewCreated = m_surveyView.Create(IDD_SURVEY_VIEW_LAYER, this);
	if (!surveyViewCreated) {
		MessageBox("SurveyView â�� ���� �� �����ϴ�.");
		return -1;
	}

	m_surveyView.ShowWindow(SW_SHOW);

	SurveyTask::Survey survey(446800.614, 193000.033);
	m_surveyView.addSurvey(survey);*/

	/*
	if (CMFCToolBar::GetUserImages() == NULL)
	{
		// ����� ���� ���� ���� �̹����� �ε��մϴ�.
		if (m_UserImages.Load(_T(".\\UserImages.bmp")))
		{
			CMFCToolBar::SetUserImages(&m_UserImages);
		}
	}
	*/
	

	// �޴� ���� ������ Ȱ��ȭ�մϴ�(���� �ֱٿ� ����� ���).
	// TODO: ������� �⺻ ����� �����Ͽ� �� Ǯ�ٿ� �޴��� �ϳ� �̻��� �⺻ ����� ���Խ�ŵ�ϴ�.
	/*
	CList<UINT, UINT> lstBasicCommands;

	lstBasicCommands.AddTail(ID_FILE_NEW);
	lstBasicCommands.AddTail(ID_FILE_OPEN);
	lstBasicCommands.AddTail(ID_FILE_SAVE);
	lstBasicCommands.AddTail(ID_FILE_PRINT);
	lstBasicCommands.AddTail(ID_APP_EXIT);
	lstBasicCommands.AddTail(ID_EDIT_CUT);
	lstBasicCommands.AddTail(ID_EDIT_PASTE);
	lstBasicCommands.AddTail(ID_EDIT_UNDO);
	lstBasicCommands.AddTail(ID_APP_ABOUT);
	lstBasicCommands.AddTail(ID_VIEW_STATUS_BAR);
	lstBasicCommands.AddTail(ID_VIEW_TOOLBAR);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2003);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_VS_2005);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLUE);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_SILVER);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLACK);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_AQUA);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_WINDOWS_7);

	CMFCToolBar::SetBasicCommands(lstBasicCommands);
	*/
	// =====================================
	// SKCM TEST
//	SetTimer( 7979, 1000, NULL );
	// SKCM TEST
	// =====================================

	/*
	CCreateContext* pContext = new CCreateContext;
	pContext->m_pCurrentDoc = NULL;
//	pContext->m_pCurrentFrame = &m_MainMenuView;
	pContext->m_pLastView = NULL;
	pContext->m_pNewViewClass = RUNTIME_CLASS(CGPSMainMenuFormView);
	pContext->m_pNewDocTemplate = NULL;

	CGPSMainMenuFormView* pView = (CGPSMainMenuFormView*)CreateView(pContext,CGPSMainMenuFormView::IDD);
	pView->SetParent( &m_MainMenuView );
	CString strTabName;
//	BOOL bNameValid;
	bNameValid = strTabName.LoadString(IDS_GPSMAINMENU_TAB);
	ASSERT(bNameValid);
	m_MainMenuView.m_wndTabs.AddTab(pView, strTabName, (UINT)1);
	*/

	return 0;
}


void CMainFrame::OnWindowPosChanged(WINDOWPOS * lpWinPos)
{
	CFrameWndEx::OnWindowPosChanged(lpWinPos);
	/*if (m_surveyView) {
		HWND hCadWnd = CCadManager::GetInstance()->GetHwnd();
		RECT cadRect;
		::GetWindowRect(hCadWnd, &cadRect);
		m_surveyView.updatePos();
	}*/
}

void CMainFrame::AddTask(SurveyTask::Task task)
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return TRUE;
}

BOOL CMainFrame::CreateDockingWindows()
{
	BOOL bNameValid;
	// ��� â�� ����ϴ�.
	CString strOutputWnd;
	bNameValid = strOutputWnd.LoadString(IDS_OUTPUT_WND);
	ASSERT(bNameValid);

	const int logWindowHeight = 150;
	if (!Logger::lout.Create(strOutputWnd, this, CRect(0, 0, 150, logWindowHeight), TRUE, ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("��� â�� ������ ���߽��ϴ�.\n");
		return FALSE;
	}

	const int leftPanelWidth = 250;
	if (!m_wndTask.Create("�۾� ����", this, CRect(0, 0, leftPanelWidth, 500), TRUE, ID_VIEW_TASKWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("��� â�� ������ ���߽��ϴ�.\n");
		return FALSE;
	}

	if (!m_wndStatePane.Create("����", this, CRect(0, 0, leftPanelWidth, 250), TRUE, ID_VIEW_STATEWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("��� â�� ������ ���߽��ϴ�.\n");
		return FALSE;
	}

	SetDockingWindowIcons(theApp.m_bHiColorIcons);
	return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	HICON hOutputBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	Logger::lout.SetIcon(hOutputBarIcon, FALSE);

}

// CMainFrame ����

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG

// CMainFrame �޽��� ó����

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* �޴��� �˻��մϴ�. */);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// �⺻ Ŭ������ ���� �۾��� �����մϴ�.

	if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}


	// ��� ����� ���� ������ ����� ���� ���߸� Ȱ��ȭ�մϴ�.
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	for (int i = 0; i < iMaxUserToolbars; i ++)
	{
		CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
		if (pUserToolbar != NULL)
		{
			pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
		}
	}
	//GPS ����
    m_OldBuffLen = 0;
	m_NewBuffLen = 0;
    m_OldBuffLen_EN = 0;
	m_NewBuffLen_EN = 0;
	//Ÿ�̸�
	SetTimer(READ_FRAME_TIMER,READ_FRAME_PERIOD,NULL);
	SetTimer(READ_FRAME_TIMER_EN,READ_FRAME_PERIOD_EN,NULL);
	return TRUE;
}


void CMainFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CFrameWndEx::OnSettingChange(uFlags, lpszSection);
	Logger::lout.UpdateFonts();
}


void CMainFrame::OnVecadOpen()
{
	CCadManager *pCadManager = CCadManager::GetInstance();
	pCadManager->CadFileOpen("D:\\Work\\RTK\\RTK\\Debug\\�����8ȣ.dwg");
}

/*
void CMainFrame::OnVecadOpenlayerdlg()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CCadManager *pCadManager = CCadManager::GetInstance();
	pCadManager->CadOpenLayerDlg();
}
*/


void CMainFrame::OnDrawPoint()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CCadManager *pCadManager = CCadManager::GetInstance();
	pCadManager->DrawPoint();
}


void CMainFrame::OnDrawLine()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CCadManager *pCadManager = CCadManager::GetInstance();
	pCadManager->DrawLine();
}


void CMainFrame::OnLoadCif()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CFileDialog dlgCifOpenDlg(true,"cif","*.cif",6UL,"Cif File(*.cif)|*.cif|All File(*.*)|*.*||",this);
	dlgCifOpenDlg.DoModal();
	CString sCifFileName = dlgCifOpenDlg.GetPathName();
	CParcelManager* pParcelManager = CParcelManager::GetInstance();
	
//	if( CParcelManager::LoadCifFile( sCifFileName ) == true )
	if( pParcelManager->LoadCif( sCifFileName ) == true )
	{
		MessageBox("Cif���� �ҷ����⸦ �Ϸ��Ͽ����ϴ�.","CIF����",MB_OK);
	}
	else
	{
		MessageBox("Cif���� �ҷ����⸦ �����Ͽ����ϴ�.","CIF����",MB_OK);
	}	
}


void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	clock_t ctime = clock();

	switch( nIDEvent )
	{
	case 7979 :
		{
			static CGPSPoint ptPrev;
			if( ptPrev.GetX() == 0 && ptPrev.GetY() == 0 )
			{
				ptPrev.SetPoint( 12642.635, -9264.323, 0 );
			}
			// xpos ( -9200.000 < x < -9400.000 )
			// ypos ( 12600.000 < y < 12800.000 )
			// ���� ���� +-1.000 , +-1.000 , +-0.500
			srand( (unsigned int)time(NULL) );
			int nRand = (rand() % 2000) - 1000;
			double fXOff = (double)(( rand() % 2000 ) - 1000 ) / 1000.0;
			double fYOff = (double)(( rand() % 2000 ) - 1000 ) / 1000.0;
			double fZOff = (double)(( rand() % 1000 ) - 500 ) / 500.0;
			double fX = ptPrev.GetX() + fXOff;
			double fY = ptPrev.GetY() + fYOff;
			double fZ = ptPrev.GetZ() + fZOff;
			ptPrev.SetPoint( fX, fY, fZ );
			ptPrev.SetInputTime( CTime::GetCurrentTime() );
		}
		break;
	case READ_FRAME_TIMER:
		if(m_OldBuffLen && (m_OldBuffLen == m_NewBuffLen))
		{
		}
		else
		{
			m_OldBuffLen = m_NewBuffLen;
		}
		break;
	case RELEASE_TIMER:
		KillTimer(RELEASE_TIMER);

		break;

	case READ_FRAME_TIMER_EN:
		/*
		if(m_NewBuffLen_EN > 0 )
//		if(m_OldBuffLen_EN && (m_OldBuffLen_EN == m_NewBuffLen_EN))
		{
			*/

			/*
		}
		else
		{
			m_OldBuffLen = m_NewBuffLen;
		}
		*/
		break;
	case RELEASE_TIMER_EN:
		KillTimer(RELEASE_TIMER_EN);
		break;


	/*case AUTO_SEND_TIMER:
		if(m_CheckAutoSend && m_AutoRadio2.GetCheck())
		{
			OnBtnSend();
		}
		break;*/
	}

	CFrameWndEx::OnTimer(nIDEvent);
}



void CMainFrame::OnConnectMachine()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.


}

long CMainFrame::OnCommunication(WPARAM wParam, LPARAM lParam)
{

	m_NewBuffLen_EN = 0;

	return 0;
}

void CMainFrame::OnParentNotify(UINT message, LPARAM lParam)
{
	CFrameWndEx::OnParentNotify(message, lParam);
	/*if (m_pStateDlg) {
		delete m_pStateDlg;
		m_pStateDlg = NULL;
	}*/
}

// #########################################################
// 
int CMainFrame::GetNowOpenMainMenuIndex( int nIndex )
{
//	m_MainMenuView.
	return -1;
}
// 
// #########################################################

void CMainFrame::AddLog( CString sLog )
{
	Logger::lout.addLog(sLog);
}

void CMainFrame::OnZoomExtent()
{
	CCadManager *pCad = CCadManager::GetInstance();
	pCad->ZoomExtent();
	//m_surveyView.updatePos();
}


void CMainFrame::OnZoomIn()
{
	CCadManager *pCad = CCadManager::GetInstance();
	pCad->ZoomIn();
	//m_surveyView.updatePos();
}


void CMainFrame::OnZoomOut()
{
	CCadManager *pCad = CCadManager::GetInstance();
	pCad->ZoomOut();
	//m_surveyView.updatePos();
}


void CMainFrame::OnMoveNowposition()
{
	CCadManager *pCad = CCadManager::GetInstance();
	pCad->MoveViewForPositionSymbol(100);
	//m_surveyView.updatePos();
}


void CMainFrame::OnZoomWindow()
{
	CCadManager *pCad = CCadManager::GetInstance();
	pCad->ZoomWindow();
	//m_surveyView.updatePos();
}


void CMainFrame::OnMovePan()
{
	CCadManager *pCad = CCadManager::GetInstance();
	pCad->PanRTime();
	//m_surveyView.updatePos();
}

void CMainFrame::OnLayerOpencontroller()
{
	CCadManager *pCadManager = CCadManager::GetInstance();
	pCadManager->CadOpenLayerDlg();
}


void CMainFrame::OnDrawCircle()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CCadManager *pCadManager = CCadManager::GetInstance();
	pCadManager->DrawCircle();
}


void CMainFrame::OnDrawRectangle()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CCadManager *pCadManager = CCadManager::GetInstance();
	pCadManager->DrawRect();
}


void CMainFrame::OnDrawPolyline()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CCadManager *pCadManager = CCadManager::GetInstance();
	pCadManager->DrawPolyline();
}




void CMainFrame::OnDrawPolygon()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CCadManager *pCadManager = CCadManager::GetInstance();
	pCadManager->DrawPolygon();
}




void CMainFrame::OnDrawText()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CCadManager *pCadManager = CCadManager::GetInstance();
	pCadManager->DrawText();
}


void CMainFrame::OnViewGpssnrgraph()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	//CGPSSNRGraphDlg dlgSNRGraph;
	//dlgSNRGraph.DoModal();
}

void CMainFrame::OnViewskygraph()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.


	//CViewSkyDlg SkyDlg;
	//SkyDlg.DoModal();
}


void CMainFrame::OnViewdopgraph()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void CMainFrame::OnViewhmovegraph()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

}


void CMainFrame::OnViewvmovegraph()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

}

void CMainFrame::OnDestroy()
{
	CFrameWndEx::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}


void CMainFrame::OnExportSvy()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�
	CCadManager *pCad = CCadManager::GetInstance();
	CFileDialog dlgSelectSVYFileName(true);
	dlgSelectSVYFileName.DoModal();
	CString sSvyFileName = dlgSelectSVYFileName.GetPathName();
	pCad->ExportToSvy(sSvyFileName);
}


void CMainFrame::OnServerStart()
{	
	WorkerManager::GetInstance()->StartServer();
	updateStateDlg();
	Logger::Log("������ ���۵Ǿ����ϴ�.\nŬ���̾�Ʈ�κ��� ���� ��û�� ���� �� �ֽ��ϴ�.");
	MessageBoxA("������ ���۵Ǿ����ϴ�.\nŬ���̾�Ʈ�κ��� ���� ��û�� ���� �� �ֽ��ϴ�.", "���� ����");
}


void CMainFrame::OnServerStop()
{
	WorkerManager::GetInstance()->StopServer();
	updateStateDlg();
	Logger::Log("������ ����Ǿ����ϴ�.");

	/*auto pMenu = m_wndMenuBar.GetMenu();
	assert(pMenu);*/
	
	/*pMenu->EnableMenuItem(ID_SERVER_START, true);
	pMenu->EnableMenuItem(ID_SERVER_STOP, false);*/
}


void CMainFrame::OnUpdateServerStop(CCmdUI *pCmdUI)
{
	

	//pCmdUI->Enable(false);
}

void CMainFrame::ShowStateDlg()
{
	m_wndStatePane.Update();
}


void CMainFrame::updateStateDlg()
{
	m_wndStatePane.Update();
}

bool CMainFrame::isServerListening() const
{
	return WorkerManager::GetInstance()->IsListening();
}



void CMainFrame::OnShowLog()
{
	Logger::lout.ShowWindow(SW_SHOW);
	Logger::lout.EnableDocking(CBRS_ALIGN_ANY);
}


void CMainFrame::OnAddTask()
{
	/*TaskAddDlg taskAddDlg(this);
	if (IDOK == taskAddDlg.DoModal()) {
		Task& newTask = taskAddDlg.getTask();
		m_wndTask.appendTask(newTask);
		assert(newTask.save());
		
		m_fileManager.saveTask(newTask);

		Log::log("�۾��� ��ϵǾ����ϴ�: [�۾���: %s\t ��ǥ����: %s]", newTask.at("name"), newTask.at("lotNumber"));
	}*/
}

void CMainFrame::OnAccept(const CString& ipAddress, UINT port, int errorCode)
{
	Logger::Log("%s:%d ����", ipAddress, port);
	updateStateDlg();
}

void CMainFrame::OnReceive(const CString& ipAddress, UINT port, Json::Value props, int errorCode)
{
	Logger::Log("%s:%d %s", ipAddress, port, props["data"].asCString());
}

void CMainFrame::OnClose(const CString & ipAddress, UINT port, int errorCode)
{
	Logger::Log("%s:%d ��������", ipAddress, port);
	updateStateDlg();
}


void CMainFrame::OnSetParcel()
{
	auto taskManager = TaskManager::GetInstance();
	const std::vector<SurveyTask::Task>& tasks = taskManager->GetTasks();
	ParcelAddDlg parcelAddDlg(tasks);
	if (IDOK == parcelAddDlg.DoModal()) {
		SurveyTask::Task selectedTask;
		bool isSelected = parcelAddDlg.GetSelectedTask(selectedTask);
		if (!isSelected) return;

		auto pManager = CCadManager::GetInstance();
		std::vector<DataType::CParcel> pts = pManager->getSelectedParcels();
		selectedTask.AddParcels(pts);
		selectedTask.Store();
	}
}

void CMainFrame::OnDevTest()
{
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	auto result = std::string(buffer).substr(0, pos);
	Logger::Log("%s", result.c_str());
}


void CMainFrame::OnManageSurveyPoints()
{
	EditSurveyPointDlg dlg;
	dlg.DoModal();
}
