#include "StdAfx.h"
#include "GPSPoint.h"

namespace DataType
{
	using namespace ShapeType;

	CGPSPoint::CGPSPoint(void)
	{
		_InitValue();
	}

	CGPSPoint::CGPSPoint(const CGPSPoint& Source)
	{
		_CopyFrom( Source );
	}


	CGPSPoint::~CGPSPoint(void)
	{
	}

	// ##############################################
	// TM좌표계 X,Y에 고도값Z
	void CGPSPoint::SetPoint( double fX, double fY, double fZ )
	{
		m_fX = fX;
		m_fY = fY;
		m_fZ = fZ;
	}

	double CGPSPoint::GetX()
	{
		return m_fX;
	}

	double CGPSPoint::GetY()
	{
		return m_fY;
	}

	double CGPSPoint::GetZ()
	{
		return m_fZ;
	}
	// TM좌표계 X,Y에 고도값Z
	// ##############################################


	// #############################################
	// 입력받은 시간정보
	void CGPSPoint::SetInputTime( CTime timeInputTime )
	{
		m_timeInputTime = timeInputTime;
	}

	CTime CGPSPoint::GetInputTime()
	{
		return m_timeInputTime;
	}
	// 입력받은 시간정보
	// #############################################

	// #############################################
	// 
	void CGPSPoint::SetPointUsingLevel( int nLevel )
	{
		m_nUsingLevel = nLevel;
	}

	int CGPSPoint::GetPointUsingLevel()
	{
		return m_nUsingLevel;
	}
	// 
	// #############################################


	// ##############################################
	// 
	const CGPSPoint& CGPSPoint::operator = (const CGPSPoint& Source )
	{
		_CopyFrom( Source );
		return Source;
	}

	bool CGPSPoint::operator == ( const CGPSPoint& Source )
	{
		return _Match( Source );
	}

	bool CGPSPoint::operator != ( const CGPSPoint& Source )
	{
		return !_Match( Source );
	}

	ShapeType::CDS_Point CGPSPoint::operator = ( ShapeType::CDS_Point ptSource )
	{
		SetPoint( ptSource );
		return ptSource;
	}

	CGPSPoint::operator CDS_Point ()
	{
		return ToDSPoint();
	}

	void CGPSPoint::SetPoint( CDS_Point ptSource )
	{
		m_fX = ptSource.GetX();
		m_fY = ptSource.GetY();
		m_fZ = 0;
	}

	CDS_Point CGPSPoint::ToDSPoint()
	{
		CDS_Point ptResult;
		ptResult.SetPoint( m_fX, m_fY );
		return ptResult;
	}

	CString CGPSPoint::ToString()
	{
		CString sBuf;
		sBuf.Format("%.3f,%.3f,%.3f",m_fX,m_fY,m_fZ);
		return sBuf;
	}

	void CGPSPoint::_InitValue()
	{
		m_fX = 0.0;
		m_fY = 0.0;
		m_fZ = 0.0;
		m_timeInputTime = CTime::GetCurrentTime();
		m_nUsingLevel = 0;
	}

	void CGPSPoint::_CopyFrom( const CGPSPoint& Source )
	{
		m_fX = Source.m_fX;
		m_fY = Source.m_fY;
		m_fZ = Source.m_fZ;
		m_timeInputTime = Source.m_timeInputTime;
		m_nUsingLevel = Source.m_nUsingLevel;
	}

	bool CGPSPoint::_Match( const CGPSPoint& Source )
	{
		if( m_fX != Source.m_fX ) return false;
		if( m_fY != Source.m_fY ) return false;
		if( m_fZ != Source.m_fZ ) return false;
		return true;
	}
};