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
	// ���� ������� ���õ� �������� �����͸� �����Ѵ�.
	class CParcelManager
	{
		friend bool __LoadCif( LPCTSTR sCifPath );
		friend class CCadManager;
		friend class CVIEW_HMOVE_GRAPH;

		// ########################################
		// �̱��������� ���� �����Լ�
	protected:
		static CParcelManager* m_pThis;

	public:
		static CParcelManager* GetInstance();
		static void ReleaseInstance();
		// �̱��������� ���� �����Լ�
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
		bool ShowParcelInfoTodlg( CString sParcelKey );			// sParcelKey�� �ش��ϴ� ������ ������ �����ش�.
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
