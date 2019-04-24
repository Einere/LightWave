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
	// CadView와 그리고 VeCad에 관한 전반적인 일을 하게 될 클래스이다.
	class CCadManager
	{
		friend void __stdcall CadEventExecute(VDWG hDwg, int Command);
		friend void __stdcall EntityClick(VDWG hDwg, VHANDLE hEnt, BOOL bSelect, BOOL bFinal);
		// ########################################
		// 싱글톤패턴을 위한 접근함수
	protected:
		static CCadManager* m_pThis;

	public:
		static CCadManager* GetInstance();
		static void ReleaseInstance();
		// 싱글톤패턴을 위한 접근함수
		// ########################################



	protected:
		CCadManager(void);
	public:
		~CCadManager(void);

		// ########################################
		// 라이브러리 초기화 상태 확인
	protected:
		bool m_bInitCadLib;			// 캐드 라이브 초기화가 되었는지 여부를 기억한다.

	public:
		bool IsInitCadLib();		// 캐드 라이브 초기화가 됬는지 확인한다.
		// 라이브러리 초기화 상태 확인
		// ########################################
	
		// ########################################
		// 캐드화면 연결및 초기화 관련
	protected:
		CView* m_pMainView;			// 이 Cad화면이 부착될 View
		VDWG m_hDwg;				// Cad의 DWG
		HWND m_hWnd;				// Cad화면이 있는 실질적인 window ( m_pMainView의 자식 윈도우 )

	public:
		bool ConnectCadAndView( CView* pView );		// 부모가 될 View설정
		bool InitCadView(CView* pView = NULL );		// CadView 초기화
		bool ResizeView(int nWidth, int nHeight);	// 화면 크기 갱신
		// 캐드호면 생성및 초기화 관련
		// ########################################

		// ########################################
		//
		bool CadFileOpen(CString sFilePath);		// CadFile 열기
		bool CadOpenLayerDlg();						// 레이어 관리창 열기
		bool Execute( int nCmd );					// Cad 명령 실행
		bool ExportToSvy( CString sSvyFileName );	// SVY파일 내보내기
		//
		// ########################################

		// ########################################
		// Parcel데이터 등의 레이어를 생성한다.
	public:
		CDS_Rect m_rcViewMapRect;
		bool ReCreateParcelData();					// CParcelManager의 정보들을 바탕으로 Cad화면을 구성한다.
		// Parcel데이터 등의 레이어를 생성한다.
		// ########################################

		// ########################################
		// 레이어/도형 생성
		bool MakeLayer( CString sLayerName , int nLayerColor = CAD_COLOR_WHITE , IDOBJ idLineType = CAD_LT_CONTINUOUS , int nLineWeight = CAD_LWEIGHT_005 );
													// 레이어 생성
		bool MakePolygon( DataType::ShapeType::CDS_Polygon& plgViewPolygon, DWORD nKey, CString sExKey );
													// 폴리곤 생성
		bool MakeRect( DataType::ShapeType::CDS_Rect rcRect, DWORD nKey, CString sExKey );
													// 사각형 생성
		bool MakeText( CString sText, DataType::ShapeType::CDS_Point ptViewPos, DWORD nKey, CString sExKey , int nViewAlign = CAD_TA_CENCEN );
													// 텍스트 생성
		bool MakeCircle( double fRadius, DataType::ShapeType::CDS_Point ptViewPos, DWORD nKey, CString sExKey );
													// 원 생성
		bool MakePoint( DataType::ShapeType::CDS_Point ptViewPos, DWORD nKey, CString sExKey );
													// 점 생성
		// -------------------------------
		bool MakeBasePoint( DataType::CBasePoint ptPoint , CString sLayer = "71" );
													// 기준점 생성( Cad화면에 생성할 뿐임 )
		bool MakeLine( DataType::ShapeType::CDS_Line lnLine, CString sLayer = "" );
													// 선 생성

		bool CCadManager::MakeSurveyPoint(DataType::ShapeType::CDS_Point ptViewPos, DWORD nKey, CString sExKey);
		// 레이어/도형 생성
		// ########################################

		// ########################################
		// Draw관련
		bool DrawPoint();							// 점 그리기
		bool DrawLine();							// 선 그리기
		bool DrawCircle();							// 원 그리기
		bool DrawRect();							// 사각형 그리기
		bool DrawPolyline();
		bool DrawPolygon();							// 폴리곤 그리기
		bool DrawText();
		// Draw관련
		// ########################################

		// #######################################
		// Zoom관련
		void ZoomExtent();							// 화면에 맞춰 줌
		void ZoomIn();								// 줌인
		void ZoomOut();								// 줌아웃
		void ZoomWindow();							// 영역 줌
		void PanRTime();							// 실시간 이동
		// Zoom관련
		// #######################################

		// #######################################
		// 자기 위치 표시 관련
	protected:
		VHANDLE m_hPositionEnt;								// 현재 위치를 보여줄 Entity
		bool m_bPositionColor_Light;						// true : 밝은색 false : 어두운색
		bool m_bShowPosition;								// 위치를 보여줄지에 대한 설정값

	public:
		void InitPositionEnt();								// 위치를 보여줄 Entity 생성및 초기화
		void UpdatePosition();								// 위치 갱신
		void ShowPosition( bool bShow );					// 위치를 보여줄지에 대한 설정
		void ChangePositionColor();							// 위치 색상 변경
		void MoveViewForPositionSymbol( double fMinViewDistance );
															// 현재 위치를 기준으로 이동및 화면 확대
		bool IsPositionEnt( VHANDLE hEnt );					// 엔티티가 현재 위치를 나타내는 Entity인지 확인한다.
		void ChangePositionScale( double fScale );			// 위치를 나타내는 Entity크기 설정
	protected:
		void _ChangeBlockColor( VHANDLE hInsBlock , int nColor );
															// 인스블럭의 색상 변경
		// 자기 위치 표시 관련
		// #######################################

		// #######################################
		// 인코더 라인
	protected:
		VHANDLE m_hViewLine;								// 기계점-시준점 라인을 나타낼 Entity
		VHANDLE m_hEncorderLine;							// 기계점에서의 인코더 방향을 나타낼 Eitity
		bool m_bShowEncorderLine;							// 인코더관련 Entity들을 보여줄지에 대한 설정

	public:
		void InitEncorderLineEnt();							// 인코더 관련 Entity 생성및 초기화
		void ShowEncorderLine( bool bShow );				// 기계점-시준점 라인이 보여줄지에 대한 설정
		void ShowViewLine( bool bShow );					// 인코더 방향 라인을 보여줄지에 대한 설정
		
		bool UpdataEncorderLine();							// 인코더 라인 업데이트
		bool IsEncorderLineShow();							// 인코더 라인을 보여주고있는지에 대한 여부
		// --
		CDS_Point GetNowSelectPoint();						// 현재 선택된 점의 좌표를 가져온다.
		// 인코더 라인
		// #######################################

		// #######################################
		// 이벤트 처리
	protected:
		FnMouseClickCallback m_fnMouseClickEvent;			// 마우스 클릭됬을때 실행될 콜백 함수
	public:
		unsigned int m_nColorChangeEventHandle;				// 현재위치 Entity의 색상변경을 위한 타이머의 이벤트 ID
	public:
		void WantGetMousePoint();							// 마우스 포인트를 입력받도록 설정한다.
		void OnShowParcelInfomation();						// 선택한 도형의 필지 정보를 확인한다.

		// 현재 선택된 필지들의 리스트를 반환.
		std::vector<DataType::CParcel> getSelectedParcels();
		void OnMouseClick( double fX, double fY );			// 마우스가 클릭되었을때

		void SetMouseClickEventFunction( FnMouseClickCallback fnMouseClickEvent );
															// 마우스가 클릭 되었을때 호출될 콜백 함수 등록
		// Polyline 생성중
	public:
		void _OnPolylineEditOpenComplate();
		void _OnPolylineEditCloseComplate();
		void _OnPolylineEditCancel();
		// 이벤트 처리
		// #######################################

	public:
		HWND GetHwnd() const;
		VDWG GetVDwg() const;
		const std::vector<VHANDLE>& getSurveyHandles() const;

	private:
		std::vector<VHANDLE> m_surveyHandles;
	};
};
