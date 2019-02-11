#pragma once
#include "afxcmn.h"

#include "Parcel.h"
// CParcelInfoDlg 대화 상자입니다.

using namespace DataType;

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// 필지정보를 보여줄 다얄로그이다.
class CParcelInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CParcelInfoDlg)

public:
	CParcelInfoDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CParcelInfoDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_VIEW_PARCEL_INFORMATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

protected:
	CListCtrl m_ctrlParcelInfoList;
	CParcel* m_pViewParcel;
	bool m_bInit;
	
public:

	virtual BOOL OnInitDialog();

	void SetViewParcel( CParcel *pParcel );

protected:
	void _LoadParcelInfo();
};
