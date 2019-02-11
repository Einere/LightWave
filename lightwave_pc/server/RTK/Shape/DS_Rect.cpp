#include "StdAfx.h"
#include "DS_Rect.h"

namespace DataType
{
	namespace ShapeType
	{
		CDS_Rect::CDS_Rect(void)
		{
			m_fLeft = 0.0;
			m_fRight = 0.0;
			m_fTop = 0.0;
			m_fBottom = 0.0;
		}

		CDS_Rect::CDS_Rect(const CDS_Rect& rcSource )
		{
			_CopyFrom( rcSource );
		}

		CDS_Rect::~CDS_Rect(void)
		{

		}

		CDS_Point CDS_Rect::GetLeftTop()
		{
			CDS_Point ptTemp;
			ptTemp.SetPoint( m_fLeft, m_fTop );
			return ptTemp;
		}

		CDS_Point CDS_Rect::GetRightTop()
		{
			CDS_Point ptTemp;
			ptTemp.SetPoint( m_fRight, m_fTop );
			return ptTemp;
		}

		CDS_Point CDS_Rect::GetLeftBottom()
		{
			CDS_Point ptTemp;
			ptTemp.SetPoint( m_fLeft, m_fBottom );
			return ptTemp;
		}

		CDS_Point CDS_Rect::GetRightBottom()
		{
			CDS_Point ptTemp;
			ptTemp.SetPoint( m_fRight, m_fBottom );
			return ptTemp;
		}

		CDS_Point CDS_Rect::GetCenter()
		{
			CDS_Point ptTemp;
			ptTemp.SetPoint( ( m_fLeft + m_fRight ) / 2.0 , ( m_fTop + m_fBottom ) / 2.0 );
			return ptTemp;
		}

		bool CDS_Rect::RectExtend( CDS_Point ptTemp )
		{
			bool bExtend = false;
			if( ptTemp.GetX() < m_fLeft )
			{
				bExtend = true;
				m_fLeft = ptTemp.GetX();
			}
			if( ptTemp.GetX() > m_fRight )
			{
				bExtend = true;
				m_fRight = ptTemp.GetX();
			}
			if( ptTemp.GetY() < m_fBottom )
			{
				bExtend = true;
				m_fBottom = ptTemp.GetY();
			}
			if( ptTemp.GetY() > m_fTop )
			{
				bExtend = true;
				m_fTop = ptTemp.GetY();
			}
			return bExtend;
		}

		bool CDS_Rect::InitWithTwoPoint( CDS_Point ptTemp1, CDS_Point ptTemp2 )
		{
			if( ptTemp1.GetX() < ptTemp2.GetX() )
			{
				m_fLeft = ptTemp1.GetX();
				m_fRight = ptTemp2.GetX();
			}
			else
			{
				m_fLeft = ptTemp2.GetX();
				m_fRight = ptTemp1.GetX();
			}

			if( ptTemp1.GetY() < ptTemp2.GetY() )
			{
				m_fBottom = ptTemp1.GetY();
				m_fTop = ptTemp2.GetY();
			}
			else
			{
				m_fBottom = ptTemp2.GetY();
				m_fTop = ptTemp1.GetY();
			}

			return true;
		}

		double CDS_Rect::GetWidth()
		{
			return ( m_fRight - m_fLeft );
		}
		
		double CDS_Rect::GetHeight()
		{
			return ( m_fTop - m_fBottom );
		}

		double CDS_Rect::GetAreaSize()
		{
			return ( GetWidth() * GetHeight() );
		}

		const CDS_Rect& CDS_Rect::operator = ( const CDS_Rect& rcSource )
		{
			_CopyFrom( rcSource );
			return rcSource;
		}

		bool CDS_Rect::operator == ( const CDS_Rect& rcSource )
		{
			return _Match( rcSource );
		}

		bool CDS_Rect::operator != ( const CDS_Rect& rcSource )
		{
			return !_Match( rcSource );
		}

		
		void CDS_Rect::_CopyFrom( const CDS_Rect& rcSource )
		{
			m_fLeft = rcSource.m_fLeft;
			m_fRight = rcSource.m_fRight;
			m_fTop = rcSource.m_fTop;
			m_fBottom = rcSource.m_fBottom;
		}

		bool CDS_Rect::_Match( const CDS_Rect& rcSource )
		{
			if( m_fLeft != rcSource.m_fLeft ) return false;
			if( m_fRight != rcSource.m_fRight ) return false;
			if( m_fTop != rcSource.m_fTop ) return false;
			if( m_fBottom != rcSource.m_fBottom ) return false;

			return true;
		}
	};
};