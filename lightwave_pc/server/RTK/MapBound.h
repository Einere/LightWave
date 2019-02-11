#pragma once

#include "Shape\\DS_Point.h"
#include "Shape\\DS_Rect.h"

namespace DataType
{
	using namespace ShapeType;
	// #############################################################################
	// ������ ��Ÿ���� ������ Ŭ�����̴�.
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

		CString GetUniqKey();		// ��ô + ��ȣ
		DWORD GetEntityKey();

		CDS_Rect GetRect();
	};
};
