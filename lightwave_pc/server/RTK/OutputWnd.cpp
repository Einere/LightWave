
#include "stdafx.h"

#include "OutputWnd.h"
#include "Resource.h"
#include "GlobalUtil\\FileUtil.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace GlobalUtil;

/////////////////////////////////////////////////////////////////////////////
// COutputBar

CLogWnd::CLogWnd()
{
	m_sLogFileName = __LOG_DATA_SAVE_FILENAME__;
}

CLogWnd::~CLogWnd()
{
}

BEGIN_MESSAGE_MAP(CLogWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

int CLogWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// �� â�� ����ϴ�.
	if (!m_wndTabs.Create(CMFCTabCtrl::STYLE_FLAT, rectDummy, this, 1))
	{
		TRACE0("��� �� â�� ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}

	// ��� â�� ����ϴ�.
	const DWORD dwStyle = LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;

	if( m_wndOutputLog.Create( dwStyle,rectDummy,&m_wndTabs,2 ) == FALSE )
	{
		TRACE0("��� â�� ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}
	/*
	if (!m_wndOutputBuild.Create(dwStyle, rectDummy, &m_wndTabs, 2) ||
		!m_wndOutputDebug.Create(dwStyle, rectDummy, &m_wndTabs, 3) ||
		!m_wndOutputFind.Create(dwStyle, rectDummy, &m_wndTabs, 4))
	{
		TRACE0("��� â�� ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}
	*/

	UpdateFonts();

	CString strTabName;
	BOOL bNameValid;

	// �ǿ� ��� â�� �����մϴ�.
	bNameValid = strTabName.LoadString(IDS_TAB_TITLE_LOGOUTPUT);
	ASSERT(bNameValid);
	m_wndTabs.AddTab(&m_wndOutputLog, strTabName, (UINT)0 );
	/*
	m_wndTabs.AddTab(&m_wndOutputBuild, strTabName, (UINT)0);
	bNameValid = strTabName.LoadString(IDS_DEBUG_TAB);
	ASSERT(bNameValid);
	m_wndTabs.AddTab(&m_wndOutputDebug, strTabName, (UINT)1);
	bNameValid = strTabName.LoadString(IDS_FIND_TAB);
	ASSERT(bNameValid);
	m_wndTabs.AddTab(&m_wndOutputFind, strTabName, (UINT)2);
	*/

	// ��� ���� ���� �ؽ�Ʈ�� ä��ϴ�.
	/*
	FillBuildWindow();
	FillDebugWindow();
	FillFindWindow();
	*/

	return 0;
}

void CLogWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// Tab ��Ʈ���� ��ü Ŭ���̾�Ʈ ������ ó���ؾ� �մϴ�.
	m_wndTabs.SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void CLogWnd::AdjustHorzScroll(CListBox& wndListBox)
{
	CClientDC dc(this);
	CFont* pOldFont = dc.SelectObject(&afxGlobalData.fontRegular);

	int cxExtentMax = 0;

	for (int i = 0; i < wndListBox.GetCount(); i ++)
	{
		CString strItem;
		wndListBox.GetText(i, strItem);

		cxExtentMax = max(cxExtentMax, dc.GetTextExtent(strItem).cx);
	}

	wndListBox.SetHorizontalExtent(cxExtentMax);
	dc.SelectObject(pOldFont);
}

/*
void COutputWnd::FillBuildWindow()
{
	m_wndOutputBuild.AddString(_T("���⿡ ���� ����� ǥ�õ˴ϴ�."));
	m_wndOutputBuild.AddString(_T("����� ��� �� �࿡ ǥ�õ�����"));
	m_wndOutputBuild.AddString(_T("ǥ�� ����� ���ϴ� ��� ������ �� �ֽ��ϴ�."));
}

void COutputWnd::FillDebugWindow()
{
	m_wndOutputDebug.AddString(_T("���⿡ ����� ����� ǥ�õ˴ϴ�."));
	m_wndOutputDebug.AddString(_T("����� ��� �� �࿡ ǥ�õ�����"));
	m_wndOutputDebug.AddString(_T("ǥ�� ����� ���ϴ� ��� ������ �� �ֽ��ϴ�."));
}


void COutputWnd::FillFindWindow()
{
	m_wndOutputFind.AddString(_T("���⿡ ã�� ����� ǥ�õ˴ϴ�."));
	m_wndOutputFind.AddString(_T("����� ��� �� �࿡ ǥ�õ�����"));
	m_wndOutputFind.AddString(_T("ǥ�� ����� ���ϴ� ��� ������ �� �ֽ��ϴ�."));
}
*/

void CLogWnd::UpdateFonts()
{
	m_wndOutputLog.SetFont(&afxGlobalData.fontRegular);
	/*
	m_wndOutputBuild.SetFont(&afxGlobalData.fontRegular);
	m_wndOutputDebug.SetFont(&afxGlobalData.fontRegular);
	m_wndOutputFind.SetFont(&afxGlobalData.fontRegular);
	*/
}

void CLogWnd::addLog( CString sLog )
{
	sLog = sLog.Trim();	
	if( m_wndOutputLog.GetSafeHwnd() == NULL ) return;		
	m_wndOutputLog.AddString( sLog );
	int nCount = m_wndOutputLog.GetCount();
	m_wndOutputLog.SetCaretIndex(nCount -1);
	saveLog(sLog);
}

void CLogWnd::saveLog(CString sLog)
{
	if( sLog == "" ) return;	
	
	CFileUtil flLogFile;
	flLogFile.FileOpen(m_sLogFileName,"a+");
	flLogFile.MovePos( flLogFile.GetEndPos() );

	flLogFile.WriteLine( sLog );
	flLogFile.FileClose();
}

/////////////////////////////////////////////////////////////////////////////
// COutputList1

COutputList::COutputList()
{
}

COutputList::~COutputList()
{
}

BEGIN_MESSAGE_MAP(COutputList, CListBox)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_COMMAND(ID_VIEW_OUTPUTWND, OnViewOutput)
	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// COutputList �޽��� ó����

void COutputList::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	CMenu menu;
	menu.LoadMenu(IDR_OUTPUT_POPUP);

	CMenu* pSumMenu = menu.GetSubMenu(0);

	if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CMDIFrameWndEx)))
	{
		CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;

		if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
			return;

		((CMDIFrameWndEx*)AfxGetMainWnd())->OnShowPopupMenu(pPopupMenu);
		UpdateDialogControls(this, FALSE);
	}

	SetFocus();
}

void COutputList::OnEditCopy()
{
	MessageBox(_T("��� ����"));
}

void COutputList::OnEditClear()
{
	MessageBox(_T("��� �����"));
}

void COutputList::OnViewOutput()
{
	CDockablePane* pParentBar = DYNAMIC_DOWNCAST(CDockablePane, GetOwner());
	CMDIFrameWndEx* pMainFrame = DYNAMIC_DOWNCAST(CMDIFrameWndEx, GetTopLevelFrame());

	if (pMainFrame != NULL && pParentBar != NULL)
	{
		pMainFrame->SetFocus();
		pMainFrame->ShowPane(pParentBar, FALSE, FALSE, FALSE);
		pMainFrame->RecalcLayout();

	}
}




void CLogWnd::OnDestroy()
{
	CDockablePane::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}
