#include "StdAfx.h"
#include "BasePoint.h"
#include "Shape\\DS_Point.h"


namespace DataType
{
	using namespace ShapeType;

	CBasePoint::CBasePoint(void)
	{
		_InitValue();
	}

	CBasePoint::CBasePoint( const CBasePoint& Source )
	{
		_CopyFrom( Source );
	}


	CBasePoint::~CBasePoint(void)
	{
	}

	bool CBasePoint::SettingBastPointFromCifString( CString sPointData )
	{

		return false;
	}

	bool CBasePoint::SettingBasePointFromCifFile( CStdioFile& flCifFile )
	{
		_InitValue();

		CString sTagBuf;
		CString sReadBuf;
		CString sDataBuf;
		while( true )
		{
			long nPos = flCifFile.GetPosition();
			flCifFile.ReadString( sReadBuf );
			sReadBuf = sReadBuf.Trim();
			if( sReadBuf[0] == '<' )
			{
				flCifFile.Seek( nPos, CFile::begin );
				if( m_sName != "" ) return true;
				else return false;
			}
			if( sReadBuf[0] != ':' )
			{
				continue;
			}
			if( sReadBuf == ":점명" )
			{
				flCifFile.ReadString( sReadBuf );
				sReadBuf = sReadBuf.Trim();
				m_sName = sReadBuf;
				continue;
			}
			if( sReadBuf == ":좌표" )
			{
				flCifFile.ReadString( sReadBuf );
				CDS_Point ptRead;
				ptRead.InitWithCifString( sReadBuf );
				m_ptPoint = ptRead;				
				continue;
			}			
			if( sReadBuf == ":기준점종류코드" )
			{
				flCifFile.ReadString( sReadBuf );
				sReadBuf = sReadBuf.Trim();
				m_sTypeCode = sReadBuf;
				continue;
			}
			if( sReadBuf == ":원점코드" )
			{
				flCifFile.ReadString( sReadBuf );
				sReadBuf = sReadBuf.Trim();
				m_sAxisBasePointCode = sReadBuf;
				continue;
			}
			if( sReadBuf == ":상태" )
			{
				flCifFile.ReadString( sReadBuf );
				sReadBuf = sReadBuf.Trim();
				m_sState = sReadBuf;
				continue;
			}
		}
	}

	CString CBasePoint::GetPointName()
	{
		return m_sName;
	}

	CString CBasePoint::GetUniqKey()	
	{
		return GetPointName();
	}

	DWORD CBasePoint::GetEntityKey()
	{
		return m_nKey;
	}

	CGPSPoint CBasePoint::GetPosition()
	{
		return m_ptPoint;
	}

	int CBasePoint::GetKey()
	{
		return m_nKey;
	}

	void CBasePoint::SetPosition( CGPSPoint ptPosition )
	{
		m_ptPoint = ptPosition;
	}

	void CBasePoint::SetPointName( CString sName )
	{
		m_sName = sName;
	}

	void CBasePoint::SetKey( int nKey )
	{
		m_nKey = nKey;
	}

	CTime CBasePoint::GetSurveyTime()
	{
		return m_ptPoint.GetInputTime();
	}

	const CBasePoint& CBasePoint::operator = ( const CBasePoint& Source )
	{
		_CopyFrom( Source );
		return Source;
	}

	bool CBasePoint::operator == ( const CBasePoint& Source )
	{
		return _Match( Source );
	}

	bool CBasePoint::operator != ( const CBasePoint& Source )
	{
		return !_Match( Source );
	}

	// ---------------------------
	// 형변환 관련

	CString CBasePoint::ToString(bool bSimple)
	{
		CString sBuf;
		if( bSimple == false )
		{
			sBuf.Format("%s,%s,%s,%s,%s",m_sName,m_ptPoint.ToString(),m_sTypeCode,m_sAxisBasePointCode,m_sState);
		}
		else
		{
			sBuf.Format("%s,%s",m_sName,m_ptPoint.ToString());
		}
		return sBuf;
	}

	void CBasePoint::_CopyFrom( const CBasePoint& Source )
	{
		m_sName = Source.m_sName;
		m_ptPoint = Source.m_ptPoint;
		m_sTypeCode = Source.m_sTypeCode;
		m_sAxisBasePointCode = Source.m_sAxisBasePointCode;
		m_sState  = Source.m_sState;
		m_nKey = Source.m_nKey;
	}

	bool CBasePoint::_Match( const CBasePoint& Source )
	{
		if( m_sName != Source.m_sName ) return false;
		if( m_ptPoint != Source.m_ptPoint ) return false;
		if( m_sTypeCode != Source.m_sTypeCode ) return false;
		if( m_sAxisBasePointCode != Source.m_sAxisBasePointCode ) return false;
		if( m_sState  != Source.m_sState ) return false;		
		return true;
	}

	void CBasePoint::_InitValue()
	{
		m_sName = "";
		m_ptPoint.SetPoint(0,0,0);
		m_ptPoint.SetInputTime( CTime::GetCurrentTime() );
		m_sTypeCode = "";
		m_sAxisBasePointCode = "";
		m_sState  = "";
		m_nKey = 540;							// Key값			// 도근점 : 540 / 측량점 : 500
	}
};