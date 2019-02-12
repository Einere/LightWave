// ParcelInfoDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "RTK.h"
#include "ParcelInfoDlg.h"
#include "afxdialogex.h"


// CParcelInfoDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CParcelInfoDlg, CDialogEx)

CParcelInfoDlg::CParcelInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CParcelInfoDlg::IDD, pParent)
{
	m_pViewParcel = NULL;
	m_bInit = false;
}

CParcelInfoDlg::~CParcelInfoDlg()
{
}

void CParcelInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PARCELINFO, m_ctrlParcelInfoList);
}


BEGIN_MESSAGE_MAP(CParcelInfoDlg, CDialogEx)
END_MESSAGE_MAP()


// CParcelInfoDlg 메시지 처리기입니다.
BOOL CParcelInfoDlg::OnInitDialog()
{
	BOOL bResult = CDialog::OnInitDialog();

	CRect rcSize;
	m_ctrlParcelInfoList.GetWindowRect( rcSize );

	int nNameWidth = 100;

//	DWORD nStyle = m_ctrlParcelInfoList.GetExStyle();
	m_ctrlParcelInfoList.SetExtendedStyle( LVS_EX_REGIONAL | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );
	
	m_ctrlParcelInfoList.InsertColumn( 0, "이름" ,LVCFMT_CENTER , nNameWidth);
//	m_ctrlParcelInfoList.SetColumnWidth( 0,  );
//	m_ctrlParcelInfoList.SetColumn( 0, 
	m_ctrlParcelInfoList.InsertColumn( 1, "값" ,LVCFMT_LEFT , rcSize.Width() - nNameWidth- 5);
//	m_ctrlParcelInfoList.SetColumnWidth( 1,  );
//	m_ctrlParcelInfoList.Set

	// 고유번호, 축척, 지번,지목, 대장면적, 좌표면적, 원점코드, 
	
	m_ctrlParcelInfoList.InsertItem( 0, "고유번호" );
	m_ctrlParcelInfoList.InsertItem( 1, "지번" );
	m_ctrlParcelInfoList.InsertItem( 2, "지목" );
	m_ctrlParcelInfoList.InsertItem( 3, "축척" );
	m_ctrlParcelInfoList.InsertItem( 4, "대장면적" );
	m_ctrlParcelInfoList.InsertItem( 5, "좌표면적" );
	m_ctrlParcelInfoList.InsertItem( 6, "원점코드" );
	/*
	m_ctrlParcelInfoList.InsertItem( 0, "고유번호" );
	m_ctrlParcelInfoList.InsertItem( 1, "법정동" );
	m_ctrlParcelInfoList.InsertItem( 2, "대장구분" );
	m_ctrlParcelInfoList.InsertItem( 3, "지번" );
	m_ctrlParcelInfoList.InsertItem( 4, "대장도호" );
	m_ctrlParcelInfoList.InsertItem( 5, "도형도호" );
	m_ctrlParcelInfoList.InsertItem( 6, "축척코드" );
	m_ctrlParcelInfoList.InsertItem( 7, "지목" );
	m_ctrlParcelInfoList.InsertItem( 8, "대장면적" );
	m_ctrlParcelInfoList.InsertItem( 9, "원점코드" );
	*/



	m_bInit = true;
	_LoadParcelInfo();
	
	return bResult;
}

void CParcelInfoDlg::SetViewParcel( CParcel *pParcel )
{
	m_pViewParcel = pParcel;
	if( m_bInit == true ) _LoadParcelInfo();
}

void CParcelInfoDlg::_LoadParcelInfo()
{
	if( m_pViewParcel == NULL ) return;
	if( m_bInit == false ) return;

	CString sUniqNo = m_pViewParcel->GetUniqID();
	CString sLandNo = m_pViewParcel->GetLandNo();
	CString sLandObject = m_pViewParcel->GetLandObjectFullName();
	CString sLandScale;
	sLandScale.Format("%d",m_pViewParcel->GetScale());
	CString sAreaSizeOfReport = m_pViewParcel->GetSizeOfReport();
	CString sAreaSizeOfCalc;
	sAreaSizeOfCalc.Format("%.3f",m_pViewParcel->GetSizeOfCalcArea(3) );
	CString sBasePoint = m_pViewParcel->GetBasePointCode();


	// 고유번호 지번 지목 축척 대장면적 좌표면적 원점코드
	m_ctrlParcelInfoList.SetItemText( 0,1, sUniqNo );
	m_ctrlParcelInfoList.SetItemText( 1,1, sLandNo );
	m_ctrlParcelInfoList.SetItemText( 2,1, sLandObject );
	m_ctrlParcelInfoList.SetItemText( 3,1, sLandScale );
	m_ctrlParcelInfoList.SetItemText( 4,1, sAreaSizeOfReport );
	m_ctrlParcelInfoList.SetItemText( 5,1, sAreaSizeOfCalc );
	m_ctrlParcelInfoList.SetItemText( 6,1, sBasePoint );

	
}