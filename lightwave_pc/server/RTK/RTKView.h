
// RTKView.h : CRTKView Ŭ������ �������̽�
//

#pragma once


// �� ���α׷��� �ϳ����� View������ �� View������ CCadManager���� CadView�� ����� �ϴ°� �ܿ� Ư���� ���� ���� �������̴�.
class CRTKView : public CView
{
protected: // serialization������ ��������ϴ�.
	CRTKView();
	DECLARE_DYNCREATE(CRTKView)

// Ư���Դϴ�.
public:
	CRTKDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// �����Դϴ�.
public:
	virtual ~CRTKView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
};

#ifndef _DEBUG  // RTKView.cpp�� ����� ����
inline CRTKDoc* CRTKView::GetDocument() const
   { return reinterpret_cast<CRTKDoc*>(m_pDocument); }
#endif

