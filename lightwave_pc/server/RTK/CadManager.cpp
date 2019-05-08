#include "StdAfx.h"
#include "CadManager.h"
#include "ParcelManager.h"
#include "RTK.h"
#include "GlobalUtil\\FileUtil.h"
#include "TaskManager.h"
#include "SurveyViewManager.h"
#include <math.h>

#define __MSG_TIMER_CHANGE_POSITION_COLOR__	101

// ################################################################
// USER CM DEFINE
#define __CAD_CM_SHOW_PARCEL_INFOMATION__		CAD_CMD_CUSTOM + 1
#define __CAD_CM_GETGETXY__						CAD_CMD_CUSTOM + 2

#define __CAD_CM_REGISTER_TASK_PARCELS__			CAD_CMD_CUSTOM + 10
#define __CAD_CM_REGISTER_SURVEY_POINT__			CAD_CMD_CUSTOM + 11

// = Polyline Edit ContextMenu=
#define __CAD_CM_EDIT_PLINE_COMPLATE__			CAD_CMD_CUSTOM + 3
#define __CAD_CM_EDIT_PLINE_CLOSE_COMPLATE__	CAD_CMD_CUSTOM + 4
#define __CAD_CM_EDIT_PLINE_CANCEL__			CAD_CMD_CUSTOM + 5

using namespace DataType;
using namespace GlobalUtil;

namespace ProgramManager
{
	void __stdcall CadEventView(													// 화면이 이동하거나 크기가 변동될때 실행될 콜백함수 선언
		VDWG hDwg,          // handle to VeCAD object 
		int WinWidth,       // width of output window 
		int WinHeight,      // height of output window 
		double DwgLeft,     // left side of a drawing in output window 
		double DwgBottom,   // bottom side of a drawing in output window 
		double DwgRight,    // right side of a drawing in output window 
		double DwgTop,      // top side of a drawing in output window 
		double Scale        // visible scale of drawing in a window 
	);

	void __stdcall CadEventMouseDown(VDWG hCad, int Button, int Flags, int Xwin, int Ywin, double Xdwg, double Ydwg, double Zdwg);
	// 마우스클릭될때 실행될 콜백함수 선언
	void __stdcall CadEventMouseMove(VDWG hCad, int Button, int Flags, int Xwin, int Ywin, double Xdwg, double Ydwg, double Zdwg);
	// 마우스가 이동할때 실행될 콜백함수 선언
	void _stdcall CadEvenGetXY(unsigned long hDwg);									// 마우스 위치를 입력받을때 사용될 콜백함수 선언

	void __stdcall ChangePositionColorEvent(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
	// 현재위치색상변경을 위한 타이머 이벤트가 발생할때 실행될 콜백함수 선언
	void __stdcall CadEventCmdStart(VDWG hDwg, int Command, int nSteps);

	CCadManager* CCadManager::m_pThis = NULL;

	CCadManager* CCadManager::GetInstance()
	{
		if (m_pThis == NULL)
		{
			m_pThis = new CCadManager;
		}
		return m_pThis;
	}

	void CCadManager::ReleaseInstance()
	{
		if (m_pThis != NULL)
		{
			delete m_pThis;
			m_pThis = NULL;
		}
	}


	CCadManager::CCadManager(void)
	{
		// ============================================
		// 변수 초기화
		m_bInitCadLib = false;
		m_pMainView = NULL;
		m_hDwg = NULL;
		m_hWnd = NULL;

		// 위치
		m_hPositionEnt = NULL;
		m_bShowPosition = false;
		m_nColorChangeEventHandle = 0;

		// 인코더 선
		m_hEncorderLine = NULL;
		m_bShowEncorderLine = false;
		m_hViewLine = NULL;

		m_fnMouseClickEvent = NULL;

		// =============================================================
		// VeCad.dll 오픈
		if (CadLoadLibrary() == FALSE)
		{
			DWORD errcode = GetLastError();
			CString sMessage;
			sMessage.Format("캐드라이브러리를 열 수 없습니다. ercode=%d", errcode);

			MessageBox(NULL, sMessage, "RTK", MB_OK);
			m_bInitCadLib = false;
			exit(-1);
			return;
		}
		else
		{
			m_bInitCadLib = true;
		}
	}


	CCadManager::~CCadManager(void)
	{
		if (m_hDwg != NULL)
		{
			CadDelete(m_hDwg);
		}
		CadFreeLibrary();
	}


	bool CCadManager::IsInitCadLib()
	{
		return m_bInitCadLib;
	}


	bool CCadManager::ConnectCadAndView(CView* pView)
	{
		if (m_hDwg != NULL) return false;

		m_pMainView = pView;

		return true;
	}

	bool CCadManager::InitCadView(CView* pView)
	{
		if (m_hDwg != NULL) return false;

		// View 연결
		if (pView != NULL) ConnectCadAndView(pView);
		if (m_pMainView == NULL) return false;

		CadRegistration(1950125322);
		CadAccelSetDefault();

		CadOnEventExecute(CadEventExecute);
		CadOnEventView(CadEventView);
		CadOnEventMouseMove(CadEventMouseMove);
		CadOnEventMouseDown(CadEventMouseDown);
		//		CadOnEventCEntDisplay( CadEventCEntDisplay );
		CadOnEventCmdStart(CadEventCmdStart);
		CadPluginImageRead("jpg", "image", "ImgReadJPEG", 1);
		CadPluginImageRead("jpeg", "image", "ImgReadJPEG", 1);
		CadPluginImageRead("tif", "image", "ImgReadTIFF", 1);
		CadPluginImageRead("tiff", "image", "ImgReadTIFF", 1);
		CadPluginImageRead("gif", "image", "ImgReadGIF", 1);

		/*
		CadOnEventMouseMove( EventMouseMove );
		CadOnEventRegen( EventRegen );
		CadOnEventLoadSave( EventLoadSave );
		CadOnEventDistance( EventDistance );
		CadOnEventArea( EventArea );
		CadOnEventPrompt( EventPrompt );
		CadOnEventSelPage( EventSelPage );
		*/

		CadMenuClear(CAD_MENU_EDIT);
		CadMenuAdd(CAD_MENU_EDIT, _T("선택해제"), CAD_CMD_RESET);
		CadMenuAdd(CAD_MENU_EDIT, _T("객체정보"), CAD_CMD_ENTPROP);
		CadMenuAdd(CAD_MENU_EDIT, _T("-"), 0);  // separator
		CadMenuAdd(CAD_MENU_EDIT, _T("필지정보보기"), __CAD_CM_SHOW_PARCEL_INFOMATION__);
		CadMenuAdd(CAD_MENU_EDIT, _T("작업에 선택된 필지 등록"), __CAD_CM_REGISTER_TASK_PARCELS__);
		CadMenuAdd(CAD_MENU_EDIT, _T("선택된 점을 측량점으로 설정"), __CAD_CM_REGISTER_SURVEY_POINT__);

		//CadAddCommand(
		CadMenuClear(CAD_MENU_POLYLINE);	//CAD_CMD_PLINE_CLOSE
		CadMenuAdd(CAD_MENU_POLYLINE, _T("완료"), CAD_CMD_PLINE_ENTER);
		CadMenuAdd(CAD_MENU_POLYLINE, _T("폐압후 완료"), CAD_CMD_PLINE_CLOSE);
		CadMenuAdd(CAD_MENU_POLYLINE, _T("-"), 0);  // separator
		CadMenuAdd(CAD_MENU_POLYLINE, _T("취소"), CAD_CMD_PLINE_CANCEL);
		/*
		CadMenuAdd( CAD_MENU_POLYLINE, _T("완료"),__CAD_CM_EDIT_PLINE_COMPLATE__ );
		CadMenuAdd( CAD_MENU_POLYLINE, _T("폐압후 완료"),__CAD_CM_EDIT_PLINE_CLOSE_COMPLATE__ );
		CadMenuAdd( CAD_MENU_POLYLINE, _T("-"), 0 );  // separator
		CadMenuAdd( CAD_MENU_POLYLINE, _T("취소"), __CAD_CM_EDIT_PLINE_CANCEL__ );
		*/
		/*
		CadSetString( STR_MENU_ENTER         ,"완료");
		CadSetString( STR_MENU_CLOSED        ,"폐합후완료");
		CadSetString( STR_MENU_POLYGON       ,"폴리곤완료");
		*/
		m_hDwg = CadCreate();

		CRect rcParent;
		m_pMainView->GetWindowRect(&rcParent);

		m_hWnd = CadWndCreate(
			m_hDwg,         // handle to VeCAD object 
			m_pMainView->m_hWnd,   // handle to parent or owner window 
			CAD_WS_DEFAULT,         // window style 
			0,          // horizontal position of window 
			0,           // vertical position of window 
			rcParent.Width(),         // window width 
			rcParent.Height()         // window height 
		);

		CadSetDefaultFont("Fonts\\gulim.vcf");


		CadAddCommand(m_hDwg, __CAD_CM_GETGETXY__, "GETXY", "XY", 0, CadEvenGetXY, 0);
		//CadPutWindow( m_hDwg, m_pMainView->m_hWnd );

		MakeLayer("211", CAD_COLOR_RED);
		InitPositionEnt();
		InitEncorderLineEnt();

		return true;
	}

	bool CCadManager::ResizeView(int nWidth, int nHeight)
	{
		if (m_hDwg == NULL) return false;
		if (m_pMainView == NULL) return false;

		CRect rcParent;
		m_pMainView->GetWindowRect(&rcParent);

		bool bResult = CadWndResize(m_hWnd, 0, 0, rcParent.Width(), rcParent.Height());
		//	CadWinSize( m_hDwg, m_hWnd , 0 , nWidth, nHeight );
		//	CadRegen( m_hDwg );
		//	CadUpdate( m_hDwg );

		//	
		//	CadWinSize( m_hDwg, m_pMainView->m_hWnd , 0 , nWidth, nHeight );
		//	CadWndRedraw( m_pMainView->m_hWnd );
		return bResult;
	}

	// 캐드호면 생성및 초기화 관련
	// ########################################

	// ########################################
	//
	bool CCadManager::CadFileOpen(CString sFilePath)
	{
		//	if( m_hDwg == NULL ) return false;
		if (m_pMainView == NULL) return false;
		// BOOL CADAPI CadFileOpen (VDWG hDwg, HWND hWin, LPCTSTR szFileName);

		InitCadView();
		bool bResult = (bool)(::CadFileOpen(m_hDwg, m_pMainView->m_hWnd, sFilePath));
		if (bResult == true)
		{
			CadRecentAdd(sFilePath);
			CadUpdate(m_hDwg);
			CadRegen(m_hDwg);
			//		ForceDraw();
			InitPositionEnt();
			ZoomExtent();

		}
		return bResult;
	}

	bool CCadManager::CadOpenLayerDlg()
	{
		return Execute(CAD_CMD_LAYER);
	}

	bool CCadManager::Execute(int nCmd)
	{
		if (m_hDwg == NULL) return false;
		if (m_pMainView == NULL) return false;
		CadExecute(m_hDwg, m_pMainView->m_hWnd, nCmd);
		return true;
	}

	//////////////////////////////////////////////////////////
	// SVY파일 내보내기
	bool CCadManager::ExportToSvy(CString sSvyFileName)
	{
		CFileUtil flSvyFile;
		if (flSvyFile.FileOpen(sSvyFileName, "w+") == false)
		{
			return false;
		}
		// 현재 레이어 백업
		VHANDLE hOldLayer = CadGetCurLayer(m_hDwg);
		VHANDLE hTargetLayer = CadGetLayerByName(m_hDwg, "211");
		VHANDLE hEnt = CadLayerGetFirstEntity(hTargetLayer);
		int nEntIndex = 1;
		int nBlockIndex = 1;
		// 도형인덱스 , 타입,
		while (hEnt != NULL)
		{
			// 
			DWORD nEntType = CadEntityGetType(hEnt);
			DWORD nEntKey = CadEntityGetUserData(hEnt);

			switch (nEntType)
			{
			case CAD_ENT_LINE:
			{
				// 도형인덱스 , 타입, 시작점X, 시작점 Y, 종료점 X, 종료점 Y , 레이어 , 키
				double fX1, fY1, fZ1, fX2, fY2, fZ2;
				CadLineGetPoint1(hEnt, &fX1, &fY1, &fZ1);
				CadLineGetPoint2(hEnt, &fX2, &fY2, &fZ2);

				CString sWriteData;
				sWriteData.Format("%d,line,%.3f,%.3f,%.3f,%.3f,211,%d", nEntIndex, fY1, fX1, fY2, fX2, nEntKey);
				flSvyFile.WriteLine(sWriteData);
				nEntIndex++;
			}
			break;
			case CAD_ENT_POINT:
			{



			}
			break;
			case CAD_ENT_TEXT:
			{
				// 5,text,188523.522,205804.942,30.831,296,500
				CString sTemp;
				double fX1, fY1, fZ1;
				CadTextGetPoint(hEnt, &fX1, &fY1, &fZ1);
				CadTextGetText(hEnt, sTemp.GetBufferSetLength(50), 50);

				CString sWriteData;
				sWriteData.Format("%d,text,%.3f,%.3f,%s,211,%d", nEntIndex, fY1, fX1, sTemp, nEntKey);
				flSvyFile.WriteLine(sWriteData);
				nEntIndex++;

			}
			break;
			//case CAD_ENT_
			case CAD_ENT_ARC:
			{
				// 387,circle,188531.319,205762.919,1.000,217,500
				int nArcType = CadArcGetType(hEnt);
				if (nArcType == CAD_CIRCLE)
				{
					double fX1, fY1, fZ1;

					double fRadius = CadArcGetRadius(hEnt);
					CadArcGetCenter(hEnt, &fX1, &fY1, &fZ1);

					CString sWriteData;
					sWriteData.Format("%d,circle,%.3f,%.3f,%.3f,211,%d", nEntIndex, fY1, fX1, fRadius, nEntKey);
					flSvyFile.WriteLine(sWriteData);
					nEntIndex++;
				}
			}
			break;
			case CAD_ENT_INSBLOCK:
			{
				// 1,block,188523.912,205877.074,294,500
				CString sTemp;
				double fX1, fY1, fZ1;
				CadInsBlockGetPoint(hEnt, &fX1, &fY1, &fZ1);

				CString sWriteData;
				sWriteData.Format("%d,block,%.3f,%.3f,%s,211,%d", nBlockIndex, fY1, fX1, nEntKey);
				flSvyFile.WriteLine(sWriteData);
				nBlockIndex++;
			}
			break;
			}

			hEnt = CadLayerGetNextEntity(hTargetLayer, hEnt);
		}



		// 선택 레이어 복원
		flSvyFile.FileClose();
		CadSetCurLayer(m_hDwg, hOldLayer);

		return true;
	}

	//
	// ########################################

	// ########################################
	// Parcel데이터 등의 레이어를 생성한다.
	bool CCadManager::ReCreateParcelData()
	{
		double fXTemp = 0.0, fYTemp = 0.0;
		VHANDLE hLastParcel;


		CParcelManager* pParcelManager = CParcelManager::GetInstance();

		// 레이어 생성 : 1/60/71/100
		MakeLayer("1");
		MakeLayer("60", CAD_COLOR_RED);
		MakeLayer("71");

		VHANDLE hLayer1 = CadGetLayerByName(m_hDwg, "1");
		VHANDLE hLayer60 = CadGetLayerByName(m_hDwg, "60");
		VHANDLE hLayer71 = CadGetLayerByName(m_hDwg, "71");
		CadLayerPutColor(hLayer60, CAD_COLOR_RED);
		CadLayerPutColor(hLayer71, CAD_COLOR_RED);


		//		VHABDLE CadGetLayerByName(m_hDwg,"1");

				// 필지 생성
		CadSetCurLayer(m_hDwg, hLayer1);
		POSITION posNow = pParcelManager->m_lsParcelMap.GetStartPosition();
		while (posNow != 0)
		{
			CString sKey;
			CParcel parcelTemp;
			pParcelManager->m_lsParcelMap.GetNextAssoc(posNow, sKey, parcelTemp);


			fXTemp = parcelTemp.GetParcelShape().GetBound().GetCenter().GetX();
			fYTemp = parcelTemp.GetParcelShape().GetBound().GetCenter().GetY();

			MakePolygon(parcelTemp.GetParcelShape(), parcelTemp.GetEntityKey(), sKey);
			MakeText(parcelTemp.GetLandNo(true), parcelTemp.GetParcelShape().GetBound().GetCenter(), parcelTemp.GetEntityKey(), sKey);
		}

		// 도곽 생성
		CadSetCurLayer(m_hDwg, hLayer60);
		posNow = pParcelManager->m_lsMapBoundMap.GetStartPosition();
		while (posNow != 0)
		{
			CString sKey;
			CMapBound boundTemp;
			pParcelManager->m_lsMapBoundMap.GetNextAssoc(posNow, sKey, boundTemp);
			MakeRect(boundTemp.GetRect(), boundTemp.GetEntityKey(), sKey);
		}

		// 기준점 생성
		CadSetCurLayer(m_hDwg, hLayer71);
		posNow = pParcelManager->m_lsBasePointMap.GetStartPosition();
		while (posNow != 0)
		{
			CString sKey;
			CBasePoint ptTemp;
			pParcelManager->m_lsBasePointMap.GetNextAssoc(posNow, sKey, ptTemp);

			MakeBasePoint(ptTemp);
		}

		if (m_hPositionEnt != NULL)
		{
			double fX = fXTemp - CadEntityGetLeft(m_hPositionEnt);
			double fY = fYTemp - CadEntityGetBottom(m_hPositionEnt);
			CadEntityMove(m_hPositionEnt, fX, fY, 0);
		}
		if (m_hEncorderLine != NULL)
		{
			double fX = fXTemp - CadEntityGetLeft(m_hEncorderLine);
			double fY = fYTemp - CadEntityGetBottom(m_hEncorderLine);
			CadEntityMove(m_hEncorderLine, fX, fY, 0);
		}
		if (m_hViewLine != NULL)
		{
			double fX = fXTemp - CadEntityGetLeft(m_hViewLine);
			double fY = fYTemp - CadEntityGetBottom(m_hViewLine);
			CadEntityMove(m_hViewLine, fX, fY, 0);
		}

		CadUpdate(m_hDwg);
		CadRegen(m_hDwg);
		ZoomExtent();

		double fLeft, fTop, fBottom, fRight;
		CadGetWinRect(m_hDwg, &fLeft, &fBottom, &fRight, &fTop);
		CDS_Rect rcCadViewSize;
		rcCadViewSize.InitWithTwoPoint(CDS_Point(fLeft, fTop), CDS_Point(fRight, fBottom));

		m_rcViewMapRect = rcCadViewSize;

		return true;
	}
	// Parcel데이터 등의 레이어를 생성한다.
	// ########################################

	// ########################################
	// 레이어/도형 생성
	bool CCadManager::MakeLayer(CString sLayerName, int nLayerColor, IDOBJ idLineType, int nLineWeight)
	{
		VHANDLE hLayer = CadGetLayerByName(m_hDwg, sLayerName);
		if (hLayer != NULL)
		{
			if ((bool)(CadDeleteLayer(m_hDwg, hLayer)) == true)
			{
				hLayer = NULL;
			}
		}
		if (hLayer == NULL)
		{
			// DWG, 이름 , 라인컬러 , 라인 타입, 라인두께 
			hLayer = CadAddLayer(m_hDwg, sLayerName, nLayerColor, idLineType, nLineWeight);
		}
		if (hLayer == NULL) return false;
		return true;
	}

	bool CCadManager::MakePolygon(DataType::ShapeType::CDS_Polygon& plgViewPolygon, DWORD nKey, CString sExKey)
	{
		int nPolylineCount = plgViewPolygon.GetPolylineCount();
		for (int nPIndex = 0; nPIndex < nPolylineCount; nPIndex++)
		{
			DataType::ShapeType::CDS_Polyline* pPolyline = plgViewPolygon.GetPolyline(nPIndex);
			if (pPolyline == NULL) continue;

			CadClearVertices();
			int nPointCount = pPolyline->GetPointCount();
			for (int nPointIndex = 0; nPointIndex < nPointCount; nPointIndex++)
			{
				DataType::ShapeType::CDS_Point ptNow = pPolyline->GetPoint(nPointIndex);
				CadAddVertex(ptNow.GetX(), ptNow.GetY(), 0);
			}
			VHANDLE hNewPl = CadAddPolyline(m_hDwg, CAD_PLINE_LINEAR, TRUE);

			CadEntityPutUserData(hNewPl, nKey);
			if (sExKey != "")
			{
				CadEntityPutExData(hNewPl, sExKey.GetBuffer(), sExKey.GetLength());
			}
		}

		return true;
	}

	bool CCadManager::MakeRect(DataType::ShapeType::CDS_Rect rcRect, DWORD nKey, CString sExKey)
	{
		if (rcRect.GetAreaSize() < 0.000001)  return false;

		CadClearVertices();

		DataType::ShapeType::CDS_Point ptNow = rcRect.GetLeftTop();
		CadAddVertex(ptNow.GetX(), ptNow.GetY(), 0);

		ptNow = rcRect.GetRightTop();
		CadAddVertex(ptNow.GetX(), ptNow.GetY(), 0);

		ptNow = rcRect.GetRightBottom();
		CadAddVertex(ptNow.GetX(), ptNow.GetY(), 0);

		ptNow = rcRect.GetLeftBottom();
		CadAddVertex(ptNow.GetX(), ptNow.GetY(), 0);

		VHANDLE hNewPl = CadAddPolyline(m_hDwg, CAD_PLINE_LINEAR, TRUE);

		CadEntityPutUserData(hNewPl, nKey);
		if (sExKey != "")
		{
			CadEntityPutExData(hNewPl, sExKey.GetBuffer(), sExKey.GetLength());
		}

		return true;
	}

	bool CCadManager::MakeText(CString sText, DataType::ShapeType::CDS_Point ptViewPos, DWORD nKey, CString sExKey, int nViewAlign)
	{
		VHANDLE hText = CadAddText(m_hDwg, sText, ptViewPos.GetX(), ptViewPos.GetY(), 0);
		if (hText != NULL)
		{
			CadTextPutAlign(hText, nViewAlign);
			CadEntityPutUserData(hText, nKey);
			if (sExKey != "")
			{
				CadEntityPutExData(hText, sExKey.GetBuffer(), sExKey.GetLength());
			}
			return true;
		}
		return false;
	}

	bool CCadManager::MakeCircle(double fRadius, DataType::ShapeType::CDS_Point ptViewPos, DWORD nKey, CString sExKey)
	{
		VHANDLE hEnt = CadAddCircle(m_hDwg, ptViewPos.GetX(), ptViewPos.GetY(), 0, fRadius);
		if (hEnt != NULL)
		{
			CadEntityPutUserData(hEnt, nKey);
			if (sExKey != "")
			{
				CadEntityPutExData(hEnt, sExKey.GetBuffer(), sExKey.GetLength());
			}
			return true;
		}
		return false;
	}

	bool CCadManager::MakePoint(DataType::ShapeType::CDS_Point ptViewPos, DWORD nKey, CString sExKey)
	{
		VHANDLE hEnt = CadAddPoint(m_hDwg, ptViewPos.GetX(), ptViewPos.GetY(), 0);
		if (hEnt != NULL)
		{
			CadEntityPutUserData(hEnt, nKey);
			if (sExKey != "")
			{
				CadEntityPutExData(hEnt, sExKey.GetBuffer(), sExKey.GetLength());
			}
			return true;
		}
		return false;
	}

	bool CCadManager::MakeBasePoint(CBasePoint ptPoint, CString sLayer)
	{
		VHANDLE hOldLayerCur = CadGetCurLayer(m_hDwg);
		VHANDLE hLayer = CadGetLayerByName(m_hDwg, sLayer);
		if (hLayer == NULL)
		{
			this->MakeLayer(sLayer);
		}

		CadSetCurLayer(m_hDwg, hLayer);
		//		CBasePoint ptTemp;		
		MakePoint(ptPoint.GetPosition(), ptPoint.GetEntityKey(), ptPoint.GetUniqKey());
		MakeCircle(1.0, ptPoint.GetPosition(), ptPoint.GetEntityKey(), ptPoint.GetUniqKey());
		CDS_Point ptPoint2 = ptPoint.GetPosition();
		ptPoint2.MoveEnt(CDS_Point(1.0, 1.0));

		MakeText(ptPoint.GetPointName(), ptPoint2, ptPoint.GetEntityKey(), ptPoint.GetUniqKey(), CAD_TA_BOTLEFT);

		CadSetCurLayer(m_hDwg, hOldLayerCur);
		return true;
	}

	bool CCadManager::MakeLine(DataType::ShapeType::CDS_Line lnLine, CString sLayer)
	{
		VHANDLE hOldLayerCur = CadGetCurLayer(m_hDwg);
		VHANDLE hLayer = NULL;
		if (sLayer != "")
		{
			hLayer = CadGetLayerByName(m_hDwg, sLayer);
			if (hLayer == NULL)
			{
				this->MakeLayer(sLayer);
			}
			CadSetCurLayer(m_hDwg, hLayer);
		}

		CadAddLine(m_hDwg, lnLine.m_ptFirstPoint.GetX(), lnLine.m_ptFirstPoint.GetY(), 0.0,
			lnLine.m_ptSecondPoint.GetX(), lnLine.m_ptSecondPoint.GetY(), 0.0);


		CadSetCurLayer(m_hDwg, hOldLayerCur);

		return true;
	}
	// 레이어/도형 생성
	// ########################################

	// ########################################
	// Draw관련
	bool CCadManager::DrawPoint()
	{
		return Execute(CAD_CMD_DRAW_POINT);
	}

	bool CCadManager::DrawLine()
	{
		return Execute(CAD_CMD_DRAW_LINE);
	}

	bool CCadManager::DrawCircle()
	{
		return Execute(CAD_CMD_DRAW_CIRCLE);
	}

	bool CCadManager::DrawRect()
	{
		return Execute(CAD_CMD_DRAW_RECT);
	}

	bool CCadManager::DrawPolyline()
	{
		return Execute(CAD_CMD_DRAW_POLYLINE);
	}

	bool CCadManager::DrawPolygon()
	{
		return Execute(CAD_CMD_DRAW_POLYGON);
	}

	bool CCadManager::DrawText()
	{
		return Execute(CAD_CMD_DRAW_TEXT);
	}
	// Draw관련
	// ########################################


	// #######################################
	// Zoom관련
	void CCadManager::ZoomExtent()
	{
		Execute(CAD_CMD_ZOOM_EXT);
		CadUpdate(m_hDwg);
	}

	void CCadManager::ZoomIn()
	{
		Execute(CAD_CMD_ZOOM_IN);
		CadUpdate(m_hDwg);
	}

	void CCadManager::ZoomOut()
	{
		Execute(CAD_CMD_ZOOM_OUT);
		CadUpdate(m_hDwg);
	}

	void CCadManager::ZoomWindow()
	{
		Execute(CAD_CMD_ZOOM_WIN);
		//		CadUpdate(m_hDwg);
	}

	void CCadManager::PanRTime()
	{
		Execute(CAD_CMD_PAN_RTIME);
		//		CadUpdate(m_hDwg);
	}
	// Zoom관련
	// #######################################

	// #######################################
	// 자기 위치 표시 관련
	void CCadManager::InitPositionEnt()
	{
		if (m_hPositionEnt != NULL)
		{
			if (CadEntityGetDeleted(m_hPositionEnt) == false)
			{
				return;
			}
			else
			{
				m_hPositionEnt = NULL;
			}
		}
		VHANDLE hLayer = CadGetLayerByName(m_hDwg, "999");
		if (hLayer == NULL)
		{
			if (MakeLayer("999") == false) return;
		}

		//		
//		m_hPositionEnt = CadAddPoint( m_hDwg, ptNow.GetX(), ptNow.GetY(), ptNow.GetZ() );
		VHANDLE hPositionBlock = CadGetBlockByName(m_hDwg, "Position");
		if (hPositionBlock == NULL)
		{
			hPositionBlock = CadAddBlockFile(m_hDwg, "Use\\Position2.dxf");
			CadBlockPutName(hPositionBlock, "Position");
		}
		IDOBJ idBlock = CadBlockGetID(hPositionBlock);

		hLayer = CadGetLayerByName(m_hDwg, "999");
		IDOBJ idLayer = CadLayerGetID(hLayer);

		m_hPositionEnt = CadAddInsBlock(m_hDwg, idBlock, 0, 0, 0, 1, 0);
		CadEntityPutLayerID(m_hPositionEnt, m_hDwg, idLayer);
		CadEntityPutVisible(m_hPositionEnt, false);
		//CadMake
	}

	void CCadManager::UpdatePosition()
	{
		if (m_hPositionEnt == NULL) return;
		if (m_bShowPosition == false) return;

		//CGPSState *pGps = CGPSState::GetInstance(); 
		//CGPSPoint ptNow = pGps->GetGPSPosition();

		//CadInsBlockPutPoint( m_hPositionEnt, ptNow.GetX(), ptNow.GetY(), ptNow.GetZ() );

		CadUpdate(m_hDwg);
		//		CadRegen( m_hDwg );
		//		m_hPositionEnt
	}

	void CCadManager::ShowPosition(bool bShow)
	{
		if (m_hPositionEnt == NULL) return;
		m_bShowPosition = bShow;
		CadEntityPutVisible(m_hPositionEnt, bShow);
		if (bShow == true)
		{
			m_nColorChangeEventHandle = SetTimer(NULL, __MSG_TIMER_CHANGE_POSITION_COLOR__, 500, ChangePositionColorEvent);

		}
		else // ( bShow == false )
		{
			KillTimer(NULL, m_nColorChangeEventHandle);
		}
		CadUpdate(m_hDwg);
		//		UpdatePosition();
	}

	void CCadManager::ChangePositionColor()
	{
		if (m_hPositionEnt == NULL) return;
		if (m_bPositionColor_Light == false)	// 어두운색이라면 밝은색으로
		{
			_ChangeBlockColor(m_hPositionEnt, CAD_COLOR_GREEN);//CAD_COLOR_RED );
		}
		else // m_bLight == true		: 밝은 색이라면 어두운색으로
		{
			_ChangeBlockColor(m_hPositionEnt, CAD_COLOR_GRAY);//CAD_COLOR_BLUE );
		}
		m_bPositionColor_Light = !m_bPositionColor_Light;

	}

	void CCadManager::MoveViewForPositionSymbol(double fMinViewDistance)
	{
		if (m_hPositionEnt == NULL) return;
		if (fMinViewDistance < 10) fMinViewDistance = 10;
		double fX, fY, fZ;
		double fPrevLeft, fPrevRight, fPrevTop, fPrevBottom;
		double fRate;
		bool bApplyHeight;
		double fLeft, fRight, fTop, fBottom;
		CadInsBlockGetPoint(m_hPositionEnt, &fX, &fY, &fZ);
		CadGetWinRect(m_hDwg, &fPrevLeft, &fPrevBottom, &fPrevRight, &fPrevTop);
		double fPrevWidth, fPrevHeight;
		fPrevWidth = abs(fPrevRight - fPrevLeft);
		fPrevHeight = abs(fPrevTop - fPrevBottom);
		if (fPrevWidth < fPrevHeight)
		{
			bApplyHeight = false;
			//fRate = fPrevWidth / fMinViewDistance;
		}
		else
		{
			bApplyHeight = true;
			//fRate = fPrevHeight / fMinViewDistance;
		}
		//		if( 
		fRate = fPrevWidth / fPrevHeight;
		fLeft = fX - (fMinViewDistance * fRate);
		fRight = fX + (fMinViewDistance * fRate);
		fTop = fY + fMinViewDistance;
		fBottom = fY - fMinViewDistance;
		CadViewRect(m_hDwg, m_hWnd, fLeft, fBottom, fRight, fTop);
	}

	bool CCadManager::IsPositionEnt(VHANDLE hEnt)
	{
		if (hEnt == m_hPositionEnt) return true;
		return false;
	}

	void CCadManager::ChangePositionScale(double fScale)
	{
		if (m_hPositionEnt == NULL) return;
		CadInsBlockPutScale(m_hPositionEnt, fScale * 20);
	}

	void CCadManager::_ChangeBlockColor(VHANDLE hInsBlock, int nColor)
	{
		IDOBJ idTargetBlockID = CadInsBlockGetBlockID(hInsBlock);
		VHANDLE hBlock = CadGetBlockByID(m_hDwg, idTargetBlockID);

		VHANDLE hEntPtr = CadBlockGetFirstPtr(hBlock);
		while (hEntPtr != NULL)
		{
			VHANDLE hEnt = CadGetEntityByPtr(hEntPtr);
			CadEntityPutColor(hEnt, nColor);
			hEntPtr = CadBlockGetNextPtr(hBlock, hEntPtr);
		}
		CadEntityPutColor(m_hPositionEnt, nColor);
		CadUpdate(m_hDwg);
	}

	// 자기 위치 표시 관련
	// #######################################

	// #######################################
	// 인코더 라인
	void CCadManager::InitEncorderLineEnt()
	{
		VHANDLE hLayer = CadGetLayerByName(m_hDwg, "999");
		if (hLayer == NULL)
		{
			if (MakeLayer("999") == false) return;
		}
		hLayer = CadGetLayerByName(m_hDwg, "999");
		IDOBJ idLayer = CadLayerGetID(hLayer);
		bool bMake = true;
		if (m_hEncorderLine != NULL)
		{
			if (CadEntityGetDeleted(m_hEncorderLine) == false)
			{
				bMake = false;;
			}
			else
			{
				m_hEncorderLine = NULL;
			}
		}
		if (bMake == true)
		{
			m_hEncorderLine = CadAddLine(m_hDwg, 0, 0, 0, 1, 1, 0);
			CadEntityPutLayerID(m_hEncorderLine, m_hDwg, idLayer);
			CadEntityPutColor(m_hEncorderLine, CAD_COLOR_RED);
			CadEntityPutVisible(m_hEncorderLine, false);
			m_bShowEncorderLine = false;
		}
		bMake = true;
		if (m_hViewLine != NULL)
		{
			if (CadEntityGetDeleted(m_hViewLine) == false)
			{
				bMake = false;
			}
			else
			{
				m_hViewLine = NULL;
			}
		}
		if (bMake == true)
		{
			m_hViewLine = CadAddLine(m_hDwg, 0, 0, 0, 1, 1, 0);
			CadEntityPutLayerID(m_hViewLine, m_hDwg, idLayer);
			CadEntityPutColor(m_hViewLine, CAD_COLOR_BLUE);
			CadEntityPutVisible(m_hViewLine, false);
			m_bShowEncorderLine = false;
		}
	}

	void CCadManager::ShowEncorderLine(bool bShow)
	{
		if (m_hEncorderLine == NULL) return;
		CadEntityPutVisible(m_hEncorderLine, bShow);

		m_bShowEncorderLine = bShow;
	}

	void CCadManager::ShowViewLine(bool bShow)
	{
		if (m_hViewLine == NULL) return;
		CadEntityPutVisible(m_hViewLine, bShow);
	}


	bool CCadManager::IsEncorderLineShow()
	{
		if (m_hEncorderLine == NULL || m_bShowEncorderLine == false) return false;
		return true;
	}

	////////////////////////////////////////////
	// 현재 선택된 점의 좌표를 가져온다.
	CDS_Point CCadManager::GetNowSelectPoint()
	{
		CDS_Point ptResult;
		VHANDLE hEntPtr = CadSelGetFirstPtr(m_hDwg);
		while (hEntPtr != NULL)
		{
			bool bGetting = false;
			VHANDLE hEnt = CadGetEntityByPtr(hEntPtr);
			IDOBJ idLayer = CadEntityGetLayerID(hEnt);
			VHANDLE hLayer = CadGetLayerByID(m_hDwg, idLayer);
			CString sLayer;
			CadLayerGetName(hLayer, sLayer.GetBufferSetLength(50));
			// 점 좌표는 211과 71 에서만 가져온다.
			if (sLayer == "211" || sLayer == "71")
			{
				DWORD nType = CadEntityGetType(hEnt);
				// 점과 원 도형에서만 가져간다.
				switch (nType)
				{
				case CAD_ENT_POINT:
				{
					ptResult.SetPoint(CadPointGetX(hEnt), CadPointGetY(hEnt));
					bGetting = true;
				}
				break;
				case CAD_ENT_ARC:
				{
					int nSubType = CadArcGetType(hEnt);
					if (nSubType == CAD_CIRCLE)
					{
						ptResult.SetPoint(CadArcGetCenterX(hEnt), CadArcGetCenterY(hEnt));
						bGetting = true;
					}
				}
				break;
				}
			}
			if (bGetting == true) break;
			hEntPtr = CadSelGetNextPtr(m_hDwg, hEntPtr);
		}
		return ptResult;
	}

	// 인코더 라인
	// #######################################


	// #######################################
	// 이벤트 처리


	void CCadManager::WantGetMousePoint()
	{
		if (!CadSnapGetOn(m_hDwg))
		{
			CadSnapPutOn(m_hDwg, TRUE);
			CadSnapPutMode(m_hDwg, CAD_SNAP_ENDPOINT | CAD_SNAP_NODE);
		}

		CadExecute(m_hDwg, m_hWnd, __CAD_CM_GETGETXY__);
	}


	////////////////////////////////////////
	// 선택한 도형의 필지 정보를 확인한다.
	void CCadManager::OnShowParcelInfomation()
	{
		VHANDLE hSearchEntPtr = CadSelGetFirstPtr(m_hDwg);

		if (hSearchEntPtr != NULL)
		{
			VHANDLE hEnt = CadGetEntityByPtr(hSearchEntPtr);
			int nBuffer = CadEntityGetExDataSize(hEnt);
			CString sExKey;
			CadEntityGetExData(hEnt, sExKey.GetBufferSetLength(nBuffer));
			//MessageBox( NULL , sExKey, "고유번호 테스트",MB_OK );
			CParcelManager* pParcelManager = CParcelManager::GetInstance();
			pParcelManager->ShowParcelInfoTodlg(sExKey);
		}
	}


	std::vector<DataType::CParcel> CCadManager::getSelectedParcels()
	{
		std::vector<DataType::CParcel> parcels;

		VHANDLE hSearchEntPtr = CadSelGetFirstPtr(m_hDwg);
		while (hSearchEntPtr) {
			VHANDLE hEnt = CadGetEntityByPtr(hSearchEntPtr);

			int nBuffer = CadEntityGetExDataSize(hEnt);
			CString sParcelKey;
			CadEntityGetExData(hEnt, sParcelKey.GetBufferSetLength(nBuffer));

			CParcel& parcel = CParcelManager::GetInstance()->getParcel(sParcelKey);
			parcels.push_back(parcel);

			hSearchEntPtr = CadSelGetNextPtr(m_hDwg, hSearchEntPtr);
		}
		return parcels;
	}

	////////////////////////////////////////
	// 마우스가 클릭되었을때
	void CCadManager::OnMouseClick(double fX, double fY)
	{
		VHANDLE handle = CadGetEntityByCursor(m_hDwg);
		auto& surveyHandles = SurveyViewManager::GetInstance()->GetSurveyHandles();
		for (auto& h : surveyHandles) {
			if (h == handle) {
				double x, y, z;
				CadPointGetCoord(h, &x, &y, &z);

				auto pTaskManager = TaskManager::GetInstance();
				auto surveys = pTaskManager->GetSurveys();
				for (auto& s : surveys) {
					double srcX = s.GetX();
					double srcY = s.GetY();
					if (srcX == x && srcY == y) {
						SurveyInfoDlg dlg(s);
						if (IDOK == dlg.DoModal()) {

						}
						break;
					}
				}

				CadSelClear(m_hDwg);
				return;
			}
		}

		Logger::Log("X: %.3f, Y: %.3f", fY, fX);
		if (m_fnMouseClickEvent != NULL)
		{
			(*m_fnMouseClickEvent)(fX, fY);
		}
	}

	void __stdcall EntityClick(VDWG hDwg, VHANDLE hEnt, BOOL bSelect, BOOL bFinal)
	{
		/*Log::log("<%ul>", hEnt);
		auto pManager = CCadManager::GetInstance();
		auto& surveyHandles = pManager->getSurveyHandles();
		for (auto& s : surveyHandles) {
			Log::log("%ul", s);
			if (s == hEnt) {
				MessageBox(NULL, "됏따!", NULL, MB_OK);
			}
		}*/
	}

	////////////////////////////////////////
	// 마우스가 클릭 되었을때 호출될 콜백 함수 등록
	void CCadManager::SetMouseClickEventFunction(FnMouseClickCallback fnMouseClickEvent)
	{
		m_fnMouseClickEvent = fnMouseClickEvent;
	}

	///////////////////////////////////////////
	// 폴리라인 에디트중 완료 메뉴를 선택하였을때
	void CCadManager::_OnPolylineEditOpenComplate()
	{
		int nInputPointCount = CadCmdCountPoints(m_hDwg);
		CadAddPolyline(m_hDwg, CAD_PLINE_LINEAR, false);
		//			hDwg, CAD_PLINE_LINEAR, 1 ); 
			//	CadSetCmdParam(
	}

	///////////////////////////////////////////
	// 폴리라인 에디트중 폐쇠후 완료 메뉴를 선택하였을때
	void CCadManager::_OnPolylineEditCloseComplate()
	{
		CadAddPolyline(m_hDwg, CAD_PLINE_LINEAR, true);
	}

	///////////////////////////////////////////
	// 폴리라인 에디트를 취소하였을때
	void CCadManager::_OnPolylineEditCancel()
	{
		CadClearVertices();
	}

	HWND CCadManager::GetHwnd() const
	{
		return m_hWnd;
	}

	VDWG CCadManager::GetVDwg() const
	{
		return m_hDwg;
	}

	// 이벤트 처리
	// #######################################

	// #######################################
	//
	void __stdcall ChangePositionColorEvent(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
	{
		CCadManager* pCad = CCadManager::GetInstance();
		if (idEvent == pCad->m_nColorChangeEventHandle)
		{
			pCad->ChangePositionColor();
		}
	}

	void __stdcall CadEventExecute(VDWG hDwg, int Command)
	{
		CCadManager *pCad = CCadManager::GetInstance();
		switch (Command)
		{
		case __CAD_CM_SHOW_PARCEL_INFOMATION__:
		{
			pCad->OnShowParcelInfomation();
		}
		break;
		case __CAD_CM_REGISTER_TASK_PARCELS__:
		{
			auto pTaskManager = TaskManager::GetInstance();
			UINT id = pTaskManager->GetSelectedTaskIdOrZero();
			if (-1 == id) break;

			SurveyTask::Task* pTask;
			pTask = pTaskManager->GetTaskById(id);
			ASSERT(pTask != NULL);

			auto pCadManager = CCadManager::GetInstance();
			auto selectedParcels = pCadManager->getSelectedParcels();
			pTask->ClearParcelPoints();
			int size = pTask->AddParcels(selectedParcels);

			pTask->Store();
		}
		break;
		case __CAD_CM_REGISTER_SURVEY_POINT__:
		{
			auto pManager = CCadManager::GetInstance();

			VHANDLE hPtr = CadSelGetFirstPtr(pManager->GetVDwg());
			VHANDLE hEnt = CadGetEntityByPtr(hPtr);

			double x, y, z;
			CadPointGetCoord(hEnt, &x, &y, &z);

			auto pTask = TaskManager::GetInstance()->GetLoadedTask();
			SurveyTask::Survey survey(x, y);
			pTask->RegisterSurvey(survey);
			pTask->Store();

			Logger::Log("측량점 생성 완료: %d",survey.GetId());

			CadEntityErase(hEnt, true);
			SurveyViewManager::GetInstance()->LoadSurveysFromTask(*pTask);
		}
		break;
		/*
	// = CAD Polyline Edit ContextMenu =
	case __CAD_CM_EDIT_PLINE_COMPLATE__ :
		{
			pCad->_OnPolylineEditOpenComplate();
		}
		break;
	case __CAD_CM_EDIT_PLINE_CLOSE_COMPLATE__ :
		{
			pCad->_OnPolylineEditCloseComplate();
		}
		break;
	case __CAD_CM_EDIT_PLINE_CANCEL__ :
		{
			pCad->_OnPolylineEditCancel();
		}
		break;
		*/
		default:
		{

		}
		break;
		}
	}

	void __stdcall CadEventView(
		VDWG hDwg,          // handle to VeCAD object 
		int WinWidth,       // width of output window 
		int WinHeight,      // height of output window 
		double DwgLeft,     // left side of a drawing in output window 
		double DwgBottom,   // bottom side of a drawing in output window 
		double DwgRight,    // right side of a drawing in output window 
		double DwgTop,      // top side of a drawing in output window 
		double Scale        // visible scale of drawing in a window 
	)
	{
		static double fPrevScale = 0;
		static double fPrevLeft = 0;
		static double fPrevTop = 0;
		if (fPrevScale != Scale)
		{
			CCadManager *pCad = CCadManager::GetInstance();

			pCad->ChangePositionScale(Scale);
			fPrevScale = Scale;

		}
		if (fPrevScale != Scale || fPrevLeft != DwgLeft || fPrevTop != DwgTop)
		{
			//			double fLeft, fTop, fBottom, fRight;
			//			CadGetWinRect( m_hDwg, &fLeft, &fBottom, &fRight, &fTop );
			CCadManager *pCad = CCadManager::GetInstance();
			CDS_Rect rcCadViewSize;
			rcCadViewSize.InitWithTwoPoint(CDS_Point(DwgLeft, DwgTop), CDS_Point(DwgRight, DwgBottom));

			pCad->m_rcViewMapRect = rcCadViewSize;

		}
	}

	void __stdcall CadEventMouseDown(VDWG hCad, int Button, int Flags, int Xwin, int Ywin, double Xdwg, double Ydwg, double Zdwg)
	{
		CCadManager *pCad = CCadManager::GetInstance();
		pCad->OnMouseClick(Xdwg, Ydwg);
	}

	void __stdcall CadEventMouseMove(VDWG hCad, int Button, int Flags, int Xwin, int Ywin, double Xdwg, double Ydwg, double Zdwg)
	{
		//CString sMousePos;
		//sMousePos.Format( "X = %.3f Y = %.3f",Ydwg, Xdwg );
		//CGPSState *pGPS = CGPSState::GetInstance();
		//pGPS->SetTextOfGPSStateBar( sMousePos );
	}

	void _stdcall CadEvenGetXY(unsigned long hDwg)
	{
		double x1, y1, z1;

		CadCmdPrompt(hDwg, "Input first point:", "");
		int status = CadCmdUserInput(hDwg);
		switch (status)
		{
		case CAD_CCS_LBUTTON:
			CadCmdGetInputPoint(hDwg, &x1, &y1, &z1);
			break;
		case CAD_CCS_STRING:
		case CAD_CCS_RBUTTON:
		case CAD_CCS_ESCAPE:
		default:
			return;
		}

		CCadManager *pCad = CCadManager::GetInstance();
		pCad->OnMouseClick(x1, y1);

		//pMainFrame->GetCadView()->SendSelEntPoint(x1,y1);
	}


	void __stdcall CadEventCmdStart(VDWG hDwg, int Command, int nSteps)
	{
		/*
		CCadManager *pCad = CCadManager::GetInstance();
		switch( Command )
		{
		// = CAD Polyline Edit ContextMenu =
		case __CAD_CM_EDIT_PLINE_COMPLATE__ :
			{
				pCad->_OnPolylineEditOpenComplate();
			}
			break;
		case __CAD_CM_EDIT_PLINE_CLOSE_COMPLATE__ :
			{
				pCad->_OnPolylineEditCloseComplate();
			}
			break;
		case __CAD_CM_EDIT_PLINE_CANCEL__ :
			{
				pCad->_OnPolylineEditCancel();
			}
			break;
		default :
			{

			}
			break;
		}
		*/
	}
};