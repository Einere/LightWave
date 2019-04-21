#pragma once

#include "VeCad\cadapi.h"
#include "Shape\\DS_Polygon.h"
#include "Shape\\DS_Rect.h"
#include "Shape\\DS_Line.h"
#include "Parcel.h"
#include "BasePoint.h"

#include "SurveyInfoDlg.h"
//using namespace CadApi;
using namespace DataType::ShapeType;


namespace ProgramManager
{	
	void __stdcall CadEventExecute(VDWG hDwg, int Command);
	void __stdcall EntityClick(VDWG hDwg, VHANDLE hEnt, BOOL bSelect, BOOL bFinal);

	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// CadView�� �׸��� VeCad�� ���� �������� ���� �ϰ� �� Ŭ�����̴�.
	class CCadManager
	{
		friend void __stdcall CadEventExecute(VDWG hDwg, int Command);
		friend void __stdcall EntityClick(VDWG hDwg, VHANDLE hEnt, BOOL bSelect, BOOL bFinal);
		// ########################################
		// �̱��������� ���� �����Լ�
	protected:
		static CCadManager* m_pThis;

	public:
		static CCadManager* GetInstance();
		static void ReleaseInstance();
		// �̱��������� ���� �����Լ�
		// ########################################



	protected:
		CCadManager(void);
	public:
		~CCadManager(void);

		// ########################################
		// ���̺귯�� �ʱ�ȭ ���� Ȯ��
	protected:
		bool m_bInitCadLib;			// ĳ�� ���̺� �ʱ�ȭ�� �Ǿ����� ���θ� ����Ѵ�.

	public:
		bool IsInitCadLib();		// ĳ�� ���̺� �ʱ�ȭ�� ����� Ȯ���Ѵ�.
		// ���̺귯�� �ʱ�ȭ ���� Ȯ��
		// ########################################
	
		// ########################################
		// ĳ��ȭ�� ����� �ʱ�ȭ ����
	protected:
		CView* m_pMainView;			// �� Cadȭ���� ������ View
		VDWG m_hDwg;				// Cad�� DWG
		HWND m_hWnd;				// Cadȭ���� �ִ� �������� window ( m_pMainView�� �ڽ� ������ )

	public:
		bool ConnectCadAndView( CView* pView );		// �θ� �� View����
		bool InitCadView(CView* pView = NULL );		// CadView �ʱ�ȭ
		bool ResizeView(int nWidth, int nHeight);	// ȭ�� ũ�� ����
		// ĳ��ȣ�� ������ �ʱ�ȭ ����
		// ########################################

		// ########################################
		//
		bool CadFileOpen(CString sFilePath);		// CadFile ����
		bool CadOpenLayerDlg();						// ���̾� ����â ����
		bool Execute( int nCmd );					// Cad ��� ����
		bool ExportToSvy( CString sSvyFileName );	// SVY���� ��������
		//
		// ########################################

		// ########################################
		// Parcel������ ���� ���̾ �����Ѵ�.
	public:
		CDS_Rect m_rcViewMapRect;
		bool ReCreateParcelData();					// CParcelManager�� �������� �������� Cadȭ���� �����Ѵ�.
		// Parcel������ ���� ���̾ �����Ѵ�.
		// ########################################

		// ########################################
		// ���̾�/���� ����
		bool MakeLayer( CString sLayerName , int nLayerColor = CAD_COLOR_WHITE , IDOBJ idLineType = CAD_LT_CONTINUOUS , int nLineWeight = CAD_LWEIGHT_005 );
													// ���̾� ����
		bool MakePolygon( DataType::ShapeType::CDS_Polygon& plgViewPolygon, DWORD nKey, CString sExKey );
													// ������ ����
		bool MakeRect( DataType::ShapeType::CDS_Rect rcRect, DWORD nKey, CString sExKey );
													// �簢�� ����
		bool MakeText( CString sText, DataType::ShapeType::CDS_Point ptViewPos, DWORD nKey, CString sExKey , int nViewAlign = CAD_TA_CENCEN );
													// �ؽ�Ʈ ����
		bool MakeCircle( double fRadius, DataType::ShapeType::CDS_Point ptViewPos, DWORD nKey, CString sExKey );
													// �� ����
		bool MakePoint( DataType::ShapeType::CDS_Point ptViewPos, DWORD nKey, CString sExKey );
													// �� ����
		// -------------------------------
		bool MakeBasePoint( DataType::CBasePoint ptPoint , CString sLayer = "71" );
													// ������ ����( Cadȭ�鿡 ������ ���� )
		bool MakeLine( DataType::ShapeType::CDS_Line lnLine, CString sLayer = "" );
													// �� ����

		bool CCadManager::MakeSurveyPoint(DataType::ShapeType::CDS_Point ptViewPos, DWORD nKey, CString sExKey);
		// ���̾�/���� ����
		// ########################################

		// ########################################
		// Draw����
		bool DrawPoint();							// �� �׸���
		bool DrawLine();							// �� �׸���
		bool DrawCircle();							// �� �׸���
		bool DrawRect();							// �簢�� �׸���
		bool DrawPolyline();
		bool DrawPolygon();							// ������ �׸���
		bool DrawText();
		// Draw����
		// ########################################

		// #######################################
		// Zoom����
		void ZoomExtent();							// ȭ�鿡 ���� ��
		void ZoomIn();								// ����
		void ZoomOut();								// �ܾƿ�
		void ZoomWindow();							// ���� ��
		void PanRTime();							// �ǽð� �̵�
		// Zoom����
		// #######################################

		// #######################################
		// �ڱ� ��ġ ǥ�� ����
	protected:
		VHANDLE m_hPositionEnt;								// ���� ��ġ�� ������ Entity
		bool m_bPositionColor_Light;						// true : ������ false : ��ο��
		bool m_bShowPosition;								// ��ġ�� ���������� ���� ������

	public:
		void InitPositionEnt();								// ��ġ�� ������ Entity ������ �ʱ�ȭ
		void UpdatePosition();								// ��ġ ����
		void ShowPosition( bool bShow );					// ��ġ�� ���������� ���� ����
		void ChangePositionColor();							// ��ġ ���� ����
		void MoveViewForPositionSymbol( double fMinViewDistance );
															// ���� ��ġ�� �������� �̵��� ȭ�� Ȯ��
		bool IsPositionEnt( VHANDLE hEnt );					// ��ƼƼ�� ���� ��ġ�� ��Ÿ���� Entity���� Ȯ���Ѵ�.
		void ChangePositionScale( double fScale );			// ��ġ�� ��Ÿ���� Entityũ�� ����
	protected:
		void _ChangeBlockColor( VHANDLE hInsBlock , int nColor );
															// �ν����� ���� ����
		// �ڱ� ��ġ ǥ�� ����
		// #######################################

		// #######################################
		// ���ڴ� ����
	protected:
		VHANDLE m_hViewLine;								// �����-������ ������ ��Ÿ�� Entity
		VHANDLE m_hEncorderLine;							// ����������� ���ڴ� ������ ��Ÿ�� Eitity
		bool m_bShowEncorderLine;							// ���ڴ����� Entity���� ���������� ���� ����

	public:
		void InitEncorderLineEnt();							// ���ڴ� ���� Entity ������ �ʱ�ȭ
		void ShowEncorderLine( bool bShow );				// �����-������ ������ ���������� ���� ����
		void ShowViewLine( bool bShow );					// ���ڴ� ���� ������ ���������� ���� ����
		
		bool UpdataEncorderLine();							// ���ڴ� ���� ������Ʈ
		bool IsEncorderLineShow();							// ���ڴ� ������ �����ְ��ִ����� ���� ����
		// --
		CDS_Point GetNowSelectPoint();						// ���� ���õ� ���� ��ǥ�� �����´�.
		// ���ڴ� ����
		// #######################################

		// #######################################
		// �̺�Ʈ ó��
	protected:
		FnMouseClickCallback m_fnMouseClickEvent;			// ���콺 Ŭ�������� ����� �ݹ� �Լ�
	public:
		unsigned int m_nColorChangeEventHandle;				// ������ġ Entity�� ���󺯰��� ���� Ÿ�̸��� �̺�Ʈ ID
	public:
		void WantGetMousePoint();							// ���콺 ����Ʈ�� �Է¹޵��� �����Ѵ�.
		void OnShowParcelInfomation();						// ������ ������ ���� ������ Ȯ���Ѵ�.

		// ���� ���õ� �������� ����Ʈ�� ��ȯ.
		std::vector<DataType::CParcel> getSelectedParcels();
		void OnMouseClick( double fX, double fY );			// ���콺�� Ŭ���Ǿ�����

		void SetMouseClickEventFunction( FnMouseClickCallback fnMouseClickEvent );
															// ���콺�� Ŭ�� �Ǿ����� ȣ��� �ݹ� �Լ� ���
		// Polyline ������
	public:
		void _OnPolylineEditOpenComplate();
		void _OnPolylineEditCloseComplate();
		void _OnPolylineEditCancel();
		// �̺�Ʈ ó��
		// #######################################

	public:
		HWND GetHwnd() const;
		VDWG GetVDwg() const;
		const std::vector<VHANDLE>& getSurveyHandles() const;

	private:
		std::vector<VHANDLE> m_surveyHandles;
	};
};
