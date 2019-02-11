#pragma once

#include <afxtempl.h>

#include "Parcel.h"
#include "MapBound.h"
#include "BasePoint.h"
#include "ParcelInfoDlg.h"

using namespace DataType;

namespace ProgramManager
{
	class CCadManager;

	bool __LoadCif( LPCTSTR sCifPath );

	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// 필지 정보들과 관련된 전반적인 데이터를 관리한다.
	class CParcelManager
	{
		friend bool __LoadCif( LPCTSTR sCifPath );
		friend class CCadManager;
		friend class CVIEW_HMOVE_GRAPH;

		// ########################################
		// 싱글톤패턴을 위한 접근함수
	protected:
		static CParcelManager* m_pThis;

	public:
		static CParcelManager* GetInstance();
		static void ReleaseInstance();
		// 싱글톤패턴을 위한 접근함수
		// ########################################

	protected:
		CMap<CString,LPCTSTR,CParcel,CParcel&> m_lsParcelMap;
		CMap<CString,LPCTSTR,CMapBound,CMapBound&> m_lsMapBoundMap;
		CMap<CString,LPCTSTR,CBasePoint,CBasePoint&> m_lsBasePointMap;
		CArray<CBasePoint> m_lsNotAllocationNode;
		
	protected:
		CParcelManager(void);
	public:
		~CParcelManager(void);

		void ClearAllData();
		bool LoadCif( CString sCifFileName );

		bool IfEncryptionFile( CString sCifFileName );

	protected:
		bool _ReadCifFile( CString sFileName );

			
	
		// ###########################################
		// 
	protected:
		CParcelInfoDlg dlgParcelInfo;

	public:
		bool ShowParcelInfoTodlg( CString sParcelKey );			// sParcelKey에 해당하는 필지의 정보를 보여준다.
		// 
		// ###########################################

		// ###########################################
		// 
	public:
		bool SetNotAllocationNode( CBasePoint ptPoint );
		bool SetMakeLineOfTwoAllocationPointConnect();
		int GetCountOfNotAllocationNode();
		CBasePoint& GetNotAllocationPointOfIndex( int nIndex );


	};
};
