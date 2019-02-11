
// RTKView.cpp : CRTKView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "RTK.h"
#endif

#include "RTKDoc.h"
#include "RTKView.h"

#include "CadManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


using namespace ProgramManager;
// CRTKView

IMPLEMENT_DYNCREATE(CRTKView, CView)

BEGIN_MESSAGE_MAP(CRTKView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_WM_WINDOWPOSCHANGED()
END_MESSAGE_MAP()

// CRTKView ����/�Ҹ�

CRTKView::CRTKView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
}

CRTKView::~CRTKView()
{
}

BOOL CRTKView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.
	CCadManager* pCadManager = CCadManager::GetInstance();
	pCadManager->ConnectCadAndView( this );
//	pCadManager->InitCadView();

	return CView::PreCreateWindow(cs);
}

// CRTKView �׸���

void CRTKView::OnDraw(CDC* /*pDC*/pDC)
{
	CRTKDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	pDC->TextOutA( 10,10,"TEXT");
}

void CRTKView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CRTKView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CRTKView ����

#ifdef _DEBUG
void CRTKView::AssertValid() const
{
	CView::AssertValid();
}

void CRTKView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRTKDoc* CRTKView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRTKDoc)));
	return (CRTKDoc*)m_pDocument;
}
#endif //_DEBUG


// CRTKView �޽��� ó����


void CRTKView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
//	CCadManager* pManager = CCadManager::GetInstance();
//	pManager->ResizeView( cx, cy);
	
}


void CRTKView::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	CView::OnWindowPosChanged(lpwndpos);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	CCadManager* pManager = CCadManager::GetInstance();
	pManager->ResizeView( lpwndpos->cx, lpwndpos->cy);
}
