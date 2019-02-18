#include "StdAfx.h"
#include "MapBound.h"

namespace DataType
{
	CMapBound::CMapBound(void)
	{
	}


	CMapBound::~CMapBound(void)
	{
	}

	bool CMapBound::SettingMapBoundFromCifString( CString sMapBoundData )
	{
		return false;
	}

	bool CMapBound::SettingMapBoundFromCifFile( CStdioFile& flCifFile )
	{
		CString sReadBuf;
		while( true )
		{
			long nPos = flCifFile.GetPosition();
			flCifFile.ReadString( sReadBuf );
			sReadBuf = sReadBuf.Trim();
			if( sReadBuf[0] == '<' )
			{
				flCifFile.Seek( nPos, CFile::begin );
				if( m_nMapNo > 0 && m_nScale > 0 ) return true;
				else return false;
			}
			if( sReadBuf[0] != ':' )
			{
				continue;
			}
			if( sReadBuf == ":��ȣ" )
			{
				flCifFile.ReadString( sReadBuf );
				sReadBuf = sReadBuf.Trim();
				m_nMapNo = atoi(sReadBuf);
				continue;
			}
			if( sReadBuf == ":����" )
			{
				flCifFile.ReadString( sReadBuf );
				ShapeType::CDS_Point ptTemp;
				if( ptTemp.InitWithCifString( sReadBuf ) == true )
				{
					m_ptLeftBottom = ptTemp;
				}
				continue;
			}
			if( sReadBuf == ":���" )
			{
				flCifFile.ReadString( sReadBuf );
				ShapeType::CDS_Point ptTemp;
				if( ptTemp.InitWithCifString( sReadBuf ) == true )
				{
					m_ptRightTop = ptTemp;
				}
				continue;
			}
			if( sReadBuf == ":���̸�" )
			{
				flCifFile.ReadString( sReadBuf );
				sReadBuf = sReadBuf.Trim();
				m_sVillageName = sReadBuf;
				continue;
			}
			if( sReadBuf == ":��ô�ڵ�" )
			{
				flCifFile.ReadString( sReadBuf );
				sReadBuf = sReadBuf.Trim();
				m_nScale = atoi(sReadBuf);
				continue;
			}
			if( sReadBuf == ":�����ڵ�" )
			{
				flCifFile.ReadString( sReadBuf );
				sReadBuf = sReadBuf.Trim();
				m_sBasePointCode = sReadBuf;
				continue;
			}
			if( sReadBuf == ":��ġ����" )
			{
				flCifFile.ReadString( sReadBuf );
				sReadBuf = sReadBuf.Trim();
				m_nNumbericType = atoi(sReadBuf);
				continue;
			}

		}
		return true;
	}

	///////////////////////////////////////////////
	// ����Ű�� : ��ô + ��ȣ
	CString CMapBound::GetUniqKey()
	{
		CString sKey;
		sKey.Format("%ld",GetEntityKey() );
		return sKey;
	}

	DWORD CMapBound::GetEntityKey()
	{
		int nKey;
		if( m_nScale < 100 ) nKey = m_nScale * 1000 + m_nMapNo;
		else nKey = m_nScale * 10 + m_nMapNo;
		return nKey;
	}

	CDS_Rect CMapBound::GetRect()
	{
		CDS_Rect rcTemp;
		rcTemp.InitWithTwoPoint( m_ptLeftBottom, m_ptRightTop );
		return rcTemp;
	}
};