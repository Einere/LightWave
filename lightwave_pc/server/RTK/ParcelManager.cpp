#include "StdAfx.h"
#include "ParcelManager.h"
#include "GlobalUtil\FileUtil.h"
#include "CadManager.h"
#include "GlobalUtil\\FileUtil.h"

using namespace GlobalUtil;

namespace ProgramManager
{
	bool __LoadCif( LPCTSTR sCifPath )
	{
		CParcelManager* pManager = CParcelManager::GetInstance();
		CString sLoadFileName = sCifPath;
		pManager->LoadCif( sLoadFileName );

		return false;
	}

	CParcelManager* CParcelManager::m_pThis = NULL;

	CParcelManager* CParcelManager::GetInstance()
	{
		if( m_pThis == NULL )
		{
			m_pThis = new CParcelManager;
		}
		return m_pThis;
	}

	void CParcelManager::ReleaseInstance()
	{
		if( m_pThis != NULL )
		{
			delete m_pThis;
			m_pThis = NULL;
		}
	}



	CParcelManager::CParcelManager(void)
	{

	}


	CParcelManager::~CParcelManager(void)
	{

	}

	void CParcelManager::ClearAllData()
	{
		m_lsParcelMap.RemoveAll();
		m_lsMapBoundMap.RemoveAll();
		m_lsBasePointMap.RemoveAll();
	}

	bool CParcelManager::LoadCif( CString sCifFileName )
	{
		CString sReadPath = sCifFileName;
	
		ClearAllData();
		bool bReadResult = _ReadCifFile( sReadPath );
		if( bReadResult == false )
		{
			ClearAllData();
		}

		if( bReadResult == true )
		{
			CCadManager* pCad = CCadManager::GetInstance();
			pCad->ReCreateParcelData();
		}

		return bReadResult;
	}

	bool CParcelManager::IfEncryptionFile( CString sCifFileName )
	{
		return false;
	}


	bool CParcelManager::_ReadCifFile( CString sFileName )
	{
		// ---------------------------------------------
		// 파일 준비
		CStdioFile FReadCif;	// 읽을파일 핸들
		GlobalUtil::CFileUtil flCifFile;
		
		//.FileOpen( sFileName , "r+" ) == false )
		if( FReadCif.Open( sFileName, CFile::modeRead ) == false )
		{
			return false;
		}
		
		CString sReadBuf;
//		long nFileEndPos = flCifFile.GetEndPos();
//		flCifFile.MovePos(0);
		FReadCif.SeekToBegin();
		long nFileEndPos = FReadCif.GetLength();
		while( true )
		{
//			if( flCifFile.GetPos() >= nFileEndPos ) break;
			if( FReadCif.GetPosition() >= nFileEndPos ) break;


//			long nReadSize = flCifFile.ReadLine( sReadBuf );
//			if( nReadSize <= 0 )
//			{
//				continue;
//			}
			if( FReadCif.ReadString( sReadBuf ) == false ) break;

			sReadBuf = sReadBuf.Trim();
			if( sReadBuf == "EOF" )
			{
				// CIF끝
				break;
			}
			if( sReadBuf == "<CIF정보S>" )
			{
				/*
				// 
				nReadSize = flCifFile.ReadToEndString2("<CIF정보E>",sReadBuf);
				if( nReadSize < 0 )
				{
					// 문제 발생
					MessageBox(NULL,"CIF정보 테그쌍에 문제가 있습니다.","CIF열기",MB_OK );
					flCifFile.FileClose();
					return false;
				}
				continue;
				*/
				while( true )
				{
					if( FReadCif.ReadString( sReadBuf ) == false ) break;
					sReadBuf = sReadBuf.Trim();
					if( sReadBuf == "<CIF정보E>" ) break;
				}
				continue;
				
			}
			if( sReadBuf == "<필지S>" )
			{
				CParcel prNewParcel;
				if( prNewParcel.SettingParcelFromCifFile( FReadCif ) == true )
				{
					m_lsParcelMap.SetAt( prNewParcel.GetMapKey(), prNewParcel );
				}
				continue;
				/*
				int nNowPos = flCifFile.GetPos();
				// 레이어 1
				nReadSize = flCifFile.ReadToEndString2("<필지E>",sReadBuf);
				if( nReadSize < 0 )
				{
					// 문제 발생
					MessageBox(NULL,"필지 테그쌍에 문제가 있습니다","CIF열기",MB_OK );
					flCifFile.FileClose();
					return false;
				}
				CParcel prNewParcel;
				int nPosAddjustment = -1;
				if( prNewParcel.SettingParcelFromCifString( sReadBuf ) == true )
				{
					m_lsParcelMap.SetAt( prNewParcel.GetUniqID(), prNewParcel );
				}
				continue;
				*/
			}
			if( sReadBuf == "<기준점S>" )
			{
				// 레이어 71
				
				CBasePoint bptNewPoint;
				if( bptNewPoint.SettingBasePointFromCifFile( FReadCif ) == true )
				{
					m_lsBasePointMap.SetAt( bptNewPoint.GetPointName(), bptNewPoint );
				}				
				continue;
				/*
				
				nReadSize = flCifFile.ReadToEndString2( "<기준점E>" , sReadBuf );
				if( nReadSize < 0 )
				{
					// 문제 발생
					MessageBox(NULL,"기준점 테그쌍에 문제가 있습니다","CIF열기",MB_OK );
					flCifFile.FileClose();
					return false;
				}
				CBasePoint bptNewPoint;
				if( bptNewPoint.SettingBastPointFromCifString( sReadBuf ) == true )
				{
					m_lsBasePointMap.SetAt( bptNewPoint.GetPointName() , bptNewPoint );
				}
				continue;
				*/
			}
			if( sReadBuf == "<도곽S>" )
			{
				// 레이어 60
				CMapBound mbNewMapBound;
				if( mbNewMapBound.SettingMapBoundFromCifFile( FReadCif ) == true )
				{
					m_lsMapBoundMap.SetAt( mbNewMapBound.GetUniqKey() , mbNewMapBound );
				}
				continue;
				/*
				nReadSize = flCifFile.ReadToEndString2( "<도곽E>" , sReadBuf );
				if( nReadSize < 0 )
				{
					// 문제 발생 
					MessageBox( NULL, "도곽 테그쌍에 무제가 있습니다.", "CIF열기",MB_OK );
					flCifFile.FileClose();
					return false;
				}
				CMapBound mbNewMapBound;
				if( mbNewMapBound.SettingMapBoundFromCifString( sReadBuf ) == true )
				{
					m_lsMapBoundMap.SetAt( mbNewMapBound.GetUniqKey() , mbNewMapBound );
				}
				continue;
				*/
			}
		}
		flCifFile.FileClose();
		return true;
	}

	// ###########################################
	// 

	///////////////////////////////////////////////////////
	// sParcelKey에 해당하는 필지의 정보를 보여준다.
	bool CParcelManager::ShowParcelInfoTodlg( CString sParcelKey )
	{
		CParcel * pParcel = &(m_lsParcelMap[sParcelKey]);
		if( pParcel != NULL )
		{
			if( dlgParcelInfo.GetSafeHwnd() == NULL )
			{
				dlgParcelInfo.Create( CParcelInfoDlg::IDD );
			}
			if( dlgParcelInfo.GetSafeHwnd() == NULL )
			{
				MessageBox( NULL, "필지정보창을 생성할수 없습니다.","ERROR",MB_OK);
				return false;
			}
			dlgParcelInfo.SetViewParcel( pParcel );
			dlgParcelInfo.ShowWindow( SW_SHOW );
			return true;
		}
		return false;
	}

	CDS_Polyline* CParcelManager::GetParcelInfo(CString sParcelKey)
	{
		CParcel * pParcel = &(m_lsParcelMap[sParcelKey]);
		if (!pParcel) {
			return NULL;
		}

		CDS_Polygon& shape = pParcel->GetParcelShape();
		return shape.GetPolyline(0);
	}

	const std::vector<CDS_Point> CParcelManager::GetPointList(CString sParcelKey)
	{
		CParcel * pParcel = &(m_lsParcelMap[sParcelKey]);
		assert(pParcel);
		/*if (!pParcel) {
			
		}*/

		CDS_Polygon& shape = pParcel->GetParcelShape();
		CDS_Polyline* line = shape.GetPolyline(0);
		const int pointCount = line->GetPointCount();

		std::vector<CDS_Point> pointList;
		for (int i = 0; i < pointCount; ++i) {
			pointList.push_back(line->GetPoint(i));
			//Log::log("%.3f, %.3f", pointList[i].GetX(), pointList[i].GetY());
		}
		
		return pointList;
	}

	// 
	// ###########################################

	bool CParcelManager::SetNotAllocationNode( CBasePoint ptPoint )
	{
		m_lsNotAllocationNode.Add( ptPoint );
		CCadManager *pCad = CCadManager::GetInstance();
		pCad->MakeBasePoint( ptPoint , "211" );

		return true;
	}

	bool CParcelManager::SetMakeLineOfTwoAllocationPointConnect()
	{
		if( m_lsNotAllocationNode.GetCount() < 2 ) return false;
		int nLastIndex = m_lsNotAllocationNode.GetCount() - 1;
		CDS_Line lnTemp;
		lnTemp.SetLine( m_lsNotAllocationNode[nLastIndex-1].GetPosition() , m_lsNotAllocationNode[nLastIndex].GetPosition() );
		CCadManager *pCad = CCadManager::GetInstance();
		pCad->MakeLine( lnTemp , "211" );
	}

	int CParcelManager::GetCountOfNotAllocationNode()
	{
		return m_lsNotAllocationNode.GetCount();
	}

	CBasePoint& CParcelManager::GetNotAllocationPointOfIndex( int nIndex )
	{
		return m_lsNotAllocationNode.GetAt(nIndex);
	}

};