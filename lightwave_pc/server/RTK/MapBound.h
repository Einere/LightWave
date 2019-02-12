#pragma once

#include "Shape\\DS_Point.h"
#include "Shape\\DS_Rect.h"

namespace DataType
{
	using namespace ShapeType;
	// #############################################################################
	// 도곽을 나타내는 데이터 클래스이다.
	class CMapBound
	{
	protected:
		int m_nMapNo;
		CDS_Point m_ptLeftBottom;
		CDS_Point m_ptRightTop;
		CString m_sVillageName;
		int m_nScale;
		CString m_sBasePointCode;
		int m_nNumbericType;

	public:
		CMapBound(void);
		~CMapBound(void);

		bool SettingMapBoundFromCifString( CString sMapBoundData );
		bool SettingMapBoundFromCifFile( CStdioFile& flCifFile );

		CString GetUniqKey();		// 축척 + 도호
		DWORD GetEntityKey();

		CDS_Rect GetRect();
	};
};
