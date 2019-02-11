
// RTKView.h : CRTKView 클래스의 인터페이스
//

#pragma once


// 이 프로그램의 하나뿐인 View이지만 이 View에서는 CCadManager에게 CadView를 만들게 하는것 외에 특별한 일을 하지 않을것이다.
class CRTKView : public CView
{
protected: // serialization에서만 만들어집니다.
	CRTKView();
	DECLARE_DYNCREATE(CRTKView)

// 특성입니다.
public:
	CRTKDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 구현입니다.
public:
	virtual ~CRTKView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
};

#ifndef _DEBUG  // RTKView.cpp의 디버그 버전
inline CRTKDoc* CRTKView::GetDocument() const
   { return reinterpret_cast<CRTKDoc*>(m_pDocument); }
#endif

