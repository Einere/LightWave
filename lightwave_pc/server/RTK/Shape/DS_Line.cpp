#include "StdAfx.h"
#include "DS_Line.h"
#include <math.h>


namespace DataType
{
	namespace ShapeType
	{
		CDS_Line::CDS_Line(void)
		{
			m_ptFirstPoint.SetPoint( 0.0, 0.0 );
			m_ptSecondPoint.SetPoint( 0.0, 0.0 );
		}

		CDS_Line::CDS_Line( CDS_Point ptPoint1, CDS_Point ptPoint2 )
		{
			SetLine( ptPoint1, ptPoint2 );
		}

		CDS_Line::CDS_Line( const CDS_Line& lnSource )
		{
			_CopyFrom( lnSource );
		}

		CDS_Line::~CDS_Line()
		{

		}

		/////////////////////////////////////////////////////////////////////
		// �� ������ ���� �����Ѵ�.
		void CDS_Line::SetLine( CDS_Point ptPoint1, CDS_Point ptPoint2 )
		{
			m_ptFirstPoint = ptPoint1;
			m_ptSecondPoint = ptPoint2;
		}

		/////////////////////////////////////////////////////////////////////
		// �� ������ ���� �����Ѵ�.
		void CDS_Line::SetLine( double fX1, double fY1, double fX2, double fY2 )
		{
			SetLine( CDS_Point( fX1, fY1 ) ,  CDS_Point( fX2, fY2 ) );
		}

		/////////////////////////////////////////////////////////////////////
		// �� ���� X�����κ����� ���� 
		CAngle CDS_Line::GetAngle()
		{
			double fXCap = m_ptSecondPoint.GetX() - m_ptFirstPoint.GetX();
 			double fYCap = m_ptSecondPoint.GetY() - m_ptFirstPoint.GetY();

			if( fYCap == 0 )
			{
				if( fXCap == 0 ) 
				{
					return 0.0;
				}
				else if( fXCap > 0 ) 
				{
					return 0.0;
				}
				else if( fXCap < 0 ) 
				{
					return 180.0;
				}
			}
			else if( fXCap == 0 )
			{
				if( fYCap > 0 )
				{
					return 90.0;
				}
				else if( fYCap < 0 )
				{
					return 270.0;
				}
			}

			double fDist = GetDist();
			CAngle aTemp;
			aTemp.SetAngleFromRadian( acos( abs( fXCap ) / fDist ) );

			if( fYCap > 0 )
			{
				if( fXCap > 0 )
				{	// 1��и�
					return aTemp;
				}
				else
				{	// 2��и�
					return CAngle(180.0) - aTemp;
				}
			}
			else
			{
				if( fXCap < 0 )
				{	// 3��и�
					return CAngle(180.0) + aTemp;
				}
				else
				{	// 4��и�
					return CAngle(360.0) - aTemp;
				}
			}
			return CAngle( 0.0 );	
		}

		/////////////////////////////////////////////////////////////////////
		// Azimuth�� ������ ������ Y������ ���� �ð���������� ������ �ǹ��Ѵ�.
		CAngle CDS_Line::GetAzimuth()
		{
			CAngle aResult;
//			aResult.SetMode(true);
			aResult = CAngle( 90.0 ) - GetAngle();
			return aResult.GetRevisionAngle();
		}

		/////////////////////////////////////////////////////////////////////
		// �� ���� ����
		double CDS_Line::GetDist()
		{
			return CDS_Point::GetDistOfInsideTwoPoint( m_ptFirstPoint, m_ptSecondPoint );
		}

		const CDS_Line& CDS_Line::operator = ( const CDS_Line& lnSource )
		{
			_CopyFrom( lnSource );
			return lnSource;
		}

		bool CDS_Line::operator == ( const CDS_Line& lnSource )
		{
			return _Match( lnSource );
		}

		bool CDS_Line::operator != ( const CDS_Line& lnSource )
		{
			return !_Match( lnSource );
		}

		void CDS_Line::MoveEnt( CDS_Point ptOffset )
		{
			m_ptFirstPoint.MoveEnt( ptOffset );
			m_ptSecondPoint.MoveEnt( ptOffset );
		}

		void CDS_Line::_CopyFrom( const CDS_Line& lnSource )
		{
			m_ptFirstPoint = lnSource.m_ptFirstPoint;
			m_ptSecondPoint = lnSource.m_ptSecondPoint;
		}

		bool CDS_Line::_Match( const CDS_Line& lnSource )
		{
			if( m_ptFirstPoint != lnSource.m_ptFirstPoint ) return false;
			if( m_ptSecondPoint != lnSource.m_ptSecondPoint ) return false;
			return true;
		}

		//////////////////////////////////////////////////////////////////
		// ��1���� ���� �� 2������ �ݽð� ���������� �����̴�. 
		CAngle CDS_Line::GetInsideAngleOfTwoLine( CDS_Line lnLine1, CDS_Line lnLine2 )
		{
			CAngle aResult;
			//aResult.SetMode( true );
			CAngle aLine1Ang = lnLine1.GetAngle();
			CAngle aLine2Ang = lnLine2.GetAngle();
			aResult = aLine2Ang - aLine1Ang;

			return aResult.GetRevisionAngle();
		}

		//////////////////////////////////////////////////////////////////
		// ���̰� fDist�� X������ ���� Angle��ŭ ȸ���Ǿ��ִ� ���� ���Ѵ�.
		CDS_Line CDS_Line::CalLineOfAngleAndDist( CAngle aRotationAngle, double fDist )
		{
			double fX = cos( aRotationAngle.ToRadian() ) * fDist;
			double fY = sin( aRotationAngle.ToRadian() ) * fDist;

			return CDS_Line( CDS_Point( 0,0) , CDS_Point(fX, fY ) ) ;
		}
											
	};
};