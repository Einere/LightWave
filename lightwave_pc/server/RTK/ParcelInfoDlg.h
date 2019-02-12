#pragma once
#include "afxcmn.h"

#include "Parcel.h"
// CParcelInfoDlg ��ȭ �����Դϴ�.

using namespace DataType;

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ���������� ������ �پ�α��̴�.
class CParcelInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CParcelInfoDlg)

public:
	CParcelInfoDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CParcelInfoDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DLG_VIEW_PARCEL_INFORMATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
