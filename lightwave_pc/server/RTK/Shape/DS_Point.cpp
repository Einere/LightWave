#include "StdAfx.h"
#include "DS_Point.h"
#include <math.h>


namespace DataType
{
	namespace ShapeType
	{
		CDS_Point::CDS_Point(void)
		{
			m_fX = 0;
			m_fY = 0;
		}

		CDS_Point::CDS_Point( double fX, double fY )
		{
			m_fX = fX;
			m_fY = fY;
		}

		CDS_Point::CDS_Point(const CDS_Point& Source)
		{
			_CopyFrom( Source );
		}

		CDS_Point::~CDS_Point(void)
		{

		}

		void CDS_Point::SetPoint( double fX, double fY )
		{
			m_fX = fX;
			m_fY = fY;
		}

		double CDS_Point::GetX(int nUsingDigit)
		{
			if( nUsingDigit == -1 ) return m_fX;

			CString sTemp;
			CString sFormatMsg;
			sFormatMsg.Format("%%.%dlf",nUsingDigit);
			sTemp.Format( sFormatMsg, m_fX + 0.00000001 );

			return atof( sTemp );
		}

		double CDS_Point::GetY(int nUsingDigit)
		{
			if( nUsingDigit < 0 ) return m_fY;

			CString sTemp;
			CString sFormatMsg;
			sFormatMsg.Format("%%.%dlf",nUsingDigit);
			sTemp.Format( sFormatMsg, m_fY + 0.00000001 );
			
			return atof( sTemp );
		}

		bool CDS_Point::InitWithCifString( CString sPointCoord )
		{
			sPointCoord = sPointCoord.Trim();
			int nCuttingIndex = sPointCoord.Find(" ");
			if( nCuttingIndex < 0 ) nCuttingIndex = sPointCoord.Find("\t");
			if( nCuttingIndex < 0 ) return false;

			CString sLeft = sPointCoord.Left( nCuttingIndex );
			CString sRight = sPointCoord.Right( sPointCoord.GetLength() - nCuttingIndex  );

			m_fX = atof( sRight );
			m_fY = atof( sLeft );
			return true;
		}

		const CDS_Point& CDS_Point::operator = ( const CDS_Point& Source )
		{
			_CopyFrom( Source );
			return Source;
		}

		bool CDS_Point::operator == ( const CDS_Point& Source )
		{
			return _Match( Source );
		}

		bool CDS_Point::operator != ( const CDS_Point& Source )
		{
			return !_Match( Source );
		}

		void CDS_Point::MoveEnt( CDS_Point ptOffset )
		{
			m_fX += ptOffset.GetX();
			m_fY += ptOffset.GetY();
		}
		
		void CDS_Point::_CopyFrom( const CDS_Point& Source )
		{
			m_fX = Source.m_fX;
			m_fY = Source.m_fY;
		}

		bool CDS_Point::_Match( const CDS_Point& Source )
		{
			if( m_fX != Source.m_fX ) return false;
			if( m_fY != Source.m_fY ) return false;

			return true;
		}

		// 두점 사이의 거리이다.
		double CDS_Point::GetDistOfInsideTwoPoint( CDS_Point ptPoint1, CDS_Point ptPoint2 )
		{
			double fXCap = ptPoint2.GetX() - ptPoint1.GetX();
 			double fYCap = ptPoint2.GetY() - ptPoint1.GetY();
			
			double fDist = sqrt( fXCap * fXCap + fYCap * fYCap );
			return fDist;
		}
															
	};
};