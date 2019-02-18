
// RTKView.cpp : CRTKView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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

// CRTKView 생성/소멸

CRTKView::CRTKView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
}

CRTKView::~CRTKView()
{
}

BOOL CRTKView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.
	CCadManager* pCadManager = CCadManager::GetInstance();
	pCadManager->ConnectCadAndView( this );
//	pCadManager->InitCadView();

	return CView::PreCreateWindow(cs);
}

// CRTKView 그리기

void CRTKView::OnDraw(CDC* /*pDC*/pDC)
{
	CRTKDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
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


// CRTKView 진단

#ifdef _DEBUG
void CRTKView::AssertValid() const
{
	CView::AssertValid();
}

void CRTKView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRTKDoc* CRTKView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRTKDoc)));
	return (CRTKDoc*)m_pDocument;
}
#endif //_DEBUG


// CRTKView 메시지 처리기


void CRTKView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
//	CCadManager* pManager = CCadManager::GetInstance();
//	pManager->ResizeView( cx, cy);
	
}


void CRTKView::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	CView::OnWindowPosChanged(lpwndpos);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CCadManager* pManager = CCadManager::GetInstance();
	pManager->ResizeView( lpwndpos->cx, lpwndpos->cy);
}
