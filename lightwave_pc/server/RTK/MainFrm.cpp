
// MainFrm.cpp : CMainFrame 클래스의 구현
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
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 생성/소멸

CMainFrame::CMainFrame()
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
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
	// 보관된 값에 따라 비주얼 관리자 및 스타일을 설정합니다.
	OnApplicationLook(theApp.m_nAppLook);

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("메뉴 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// 메뉴 모음을 활성화해도 포커스가 이동하지 않게 합니다.
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	/*
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
	{
		TRACE0("도구 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
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
		TRACE0("도구 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	m_tbCadDraw.SetWindowText("CAD그림");

	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_tbCadDraw.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	if (!m_tbCadZoom.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_tbCadZoom.LoadToolBar(IDR_TB_CAD_ZOOM) )
	{
		TRACE0("도구 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	m_tbCadDraw.SetWindowText("CAD줌");
//	m_tbCadDraw.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	// 사용자 정의 도구 모음 작업을 허용합니다.
	//InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	// TODO: 도구 모음 및 메뉴 모음을 도킹할 수 없게 하려면 이 다섯 줄을 삭제하십시오.
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_tbCadDraw.EnableDocking(CBRS_ALIGN_ANY);
	m_tbCadZoom.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
//	DockPane(&m_wndToolBar);
	DockPane(&m_tbCadDraw);
	DockPane(&m_tbCadZoom);
	
	// Visual Studio 2005 스타일 도킹 창 동작을 활성화합니다.
	CDockingManager::SetDockingMode(DT_SMART);
	// Visual Studio 2005 스타일 도킹 창 자동 숨김 동작을 활성화합니다.
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// 도킹 창을 만듭니다.
	if (!CreateDockingWindows())
	{
		TRACE0("도킹 창을 만들지 못했습니다.\n");
		return -1;
	}

	Logger::lout.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&Logger::lout);

	m_wndStatePane.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndStatePane);

	m_wndTask.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndTask);

	m_wndTask.DockToWindow(&m_wndStatePane, CBRS_BOTTOM);

	// 도구 모음 및 도킹 창 메뉴 바꾸기를 활성화합니다.
	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);
//	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// 빠른(<Alt> 키를 누른 채 끌기) 도구 모음 사용자 지정을 활성화합니다.
	CMFCToolBar::EnableQuickCustomization();

	/*m_surveyView.setManager(CCadManager::GetInstance());
	BOOL surveyViewCreated = m_surveyView.Create(IDD_SURVEY_VIEW_LAYER, this);
	if (!surveyViewCreated) {
		MessageBox("SurveyView 창을 만들 수 없습니다.");
		return -1;
	}

	m_surveyView.ShowWindow(SW_SHOW);

	SurveyTask::Survey survey(446800.614, 193000.033);
	m_surveyView.addSurvey(survey);*/

	/*
	if (CMFCToolBar::GetUserImages() == NULL)
	{
		// 사용자 정의 도구 모음 이미지를 로드합니다.
		if (m_UserImages.Load(_T(".\\UserImages.bmp")))
		{
			CMFCToolBar::SetUserImages(&m_UserImages);
		}
	}
	*/
	

	// 메뉴 개인 설정을 활성화합니다(가장 최근에 사용한 명령).
	// TODO: 사용자의 기본 명령을 정의하여 각 풀다운 메뉴에 하나 이상의 기본 명령을 포함시킵니다.
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
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return TRUE;
}

BOOL CMainFrame::CreateDockingWindows()
{
	BOOL bNameValid;
	// 출력 창을 만듭니다.
	CString strOutputWnd;
	bNameValid = strOutputWnd.LoadString(IDS_OUTPUT_WND);
	ASSERT(bNameValid);

	const int logWindowHeight = 150;
	if (!Logger::lout.Create(strOutputWnd, this, CRect(0, 0, 150, logWindowHeight), TRUE, ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("출력 창을 만들지 못했습니다.\n");
		return FALSE;
	}

	const int leftPanelWidth = 250;
	if (!m_wndTask.Create("작업 정보", this, CRect(0, 0, leftPanelWidth, 500), TRUE, ID_VIEW_TASKWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("출력 창을 만들지 못했습니다.\n");
		return FALSE;
	}

	if (!m_wndStatePane.Create("상태", this, CRect(0, 0, leftPanelWidth, 250), TRUE, ID_VIEW_STATEWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("출력 창을 만들지 못했습니다.\n");
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

// CMainFrame 진단

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

// CMainFrame 메시지 처리기

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* 메뉴를 검색합니다. */);
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
	// 기본 클래스가 실제 작업을 수행합니다.

	if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}


	// 모든 사용자 도구 모음에 사용자 지정 단추를 활성화합니다.
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
	//GPS 관련
    m_OldBuffLen = 0;
	m_NewBuffLen = 0;
    m_OldBuffLen_EN = 0;
	m_NewBuffLen_EN = 0;
	//타이머
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
	pCadManager->CadFileOpen("D:\\Work\\RTK\\RTK\\Debug\\결과도8호.dwg");
}

/*
void CMainFrame::OnVecadOpenlayerdlg()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CCadManager *pCadManager = CCadManager::GetInstance();
	pCadManager->CadOpenLayerDlg();
}
*/


void CMainFrame::OnDrawPoint()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CCadManager *pCadManager = CCadManager::GetInstance();
	pCadManager->DrawPoint();
}


void CMainFrame::OnDrawLine()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CCadManager *pCadManager = CCadManager::GetInstance();
	pCadManager->DrawLine();
}


void CMainFrame::OnLoadCif()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CFileDialog dlgCifOpenDlg(true,"cif","*.cif",6UL,"Cif File(*.cif)|*.cif|All File(*.*)|*.*||",this);
	dlgCifOpenDlg.DoModal();
	CString sCifFileName = dlgCifOpenDlg.GetPathName();
	CParcelManager* pParcelManager = CParcelManager::GetInstance();
	
//	if( CParcelManager::LoadCifFile( sCifFileName ) == true )
	if( pParcelManager->LoadCif( sCifFileName ) == true )
	{
		MessageBox("Cif파일 불러오기를 완료하였습니다.","CIF열기",MB_OK);
	}
	else
	{
		MessageBox("Cif파일 불러오기를 실패하였습니다.","CIF열기",MB_OK);
	}	
}


void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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
			// 변동 범위 +-1.000 , +-1.000 , +-0.500
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
	// TODO: 여기에 명령 처리기 코드를 추가합니다.


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
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CCadManager *pCadManager = CCadManager::GetInstance();
	pCadManager->DrawCircle();
}


void CMainFrame::OnDrawRectangle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CCadManager *pCadManager = CCadManager::GetInstance();
	pCadManager->DrawRect();
}


void CMainFrame::OnDrawPolyline()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CCadManager *pCadManager = CCadManager::GetInstance();
	pCadManager->DrawPolyline();
}




void CMainFrame::OnDrawPolygon()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CCadManager *pCadManager = CCadManager::GetInstance();
	pCadManager->DrawPolygon();
}




void CMainFrame::OnDrawText()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CCadManager *pCadManager = CCadManager::GetInstance();
	pCadManager->DrawText();
}


void CMainFrame::OnViewGpssnrgraph()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	//CGPSSNRGraphDlg dlgSNRGraph;
	//dlgSNRGraph.DoModal();
}

void CMainFrame::OnViewskygraph()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.


	//CViewSkyDlg SkyDlg;
	//SkyDlg.DoModal();
}


void CMainFrame::OnViewdopgraph()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CMainFrame::OnViewhmovegraph()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

}


void CMainFrame::OnViewvmovegraph()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

}

void CMainFrame::OnDestroy()
{
	CFrameWndEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CMainFrame::OnExportSvy()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다
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
	Logger::Log("서버가 시작되었습니다.\n클라이언트로부터 연결 요청을 받을 수 있습니다.");
	MessageBoxA("서버가 시작되었습니다.\n클라이언트로부터 연결 요청을 받을 수 있습니다.", "서버 시작");
}


void CMainFrame::OnServerStop()
{
	WorkerManager::GetInstance()->StopServer();
	updateStateDlg();
	Logger::Log("서버가 종료되었습니다.");

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

		Log::log("작업이 등록되었습니다: [작업명: %s\t 대표지번: %s]", newTask.at("name"), newTask.at("lotNumber"));
	}*/
}

void CMainFrame::OnAccept(const CString& ipAddress, UINT port, int errorCode)
{
	Logger::Log("%s:%d 연결", ipAddress, port);
	updateStateDlg();
}

void CMainFrame::OnReceive(const CString& ipAddress, UINT port, Json::Value props, int errorCode)
{
	Logger::Log("%s:%d %s", ipAddress, port, props["data"].asCString());
}

void CMainFrame::OnClose(const CString & ipAddress, UINT port, int errorCode)
{
	Logger::Log("%s:%d 연결종료", ipAddress, port);
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
