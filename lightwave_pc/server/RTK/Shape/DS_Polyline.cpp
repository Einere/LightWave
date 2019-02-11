#include "StdAfx.h"
#include "DS_Polyline.h"
#include <math.h>


namespace DataType
{
	namespace ShapeType
	{
		CDS_Polyline::CDS_Polyline(void)
		{
			m_bClose = true;
		}

		CDS_Polyline::CDS_Polyline(const CDS_Polyline& Source)
		{
			_CopyFrom( Source );
		}

		CDS_Polyline::~CDS_Polyline(void)
		{
		}

		void CDS_Polyline::ClearData()
		{
			m_bClose = true;
			m_lsPointList.RemoveAll();
		}

		bool CDS_Polyline::InitWithCifStringArray(CArray<CString>& lsCifStringList,int& nCoordStartIndex,int nCoordCount )
		{
			ClearData();
			for( int nIndex = 0 ; nIndex < nCoordCount ; nIndex ++ )
			{
				CString sNowReadString = lsCifStringList[nCoordStartIndex + nIndex];
				if( sNowReadString[0] == ':' ) 
				{
					ClearData();
					return false;
				}
				CDS_Point ptTemp;
				if( ptTemp.InitWithCifString( sNowReadString ) == false )
				{
					ClearData();
					return false;
				}
				m_lsPointList.Add( ptTemp );
			}
			nCoordStartIndex = nCoordStartIndex + nCoordCount;
			_CalcBound();
			return true;
		}

		bool CDS_Polyline::InitWithCifFile( CStdioFile& flCifFile, int nPointCount )
		{
			CString sReadBuf;
			for( int nPIndex = 0 ; nPIndex < nPointCount ; nPIndex ++ )
			{
				flCifFile.ReadString( sReadBuf );
				sReadBuf = sReadBuf.Trim();
				if( sReadBuf[0] == ':' ) 
				{
					ClearData();
					return false;
				}
				CDS_Point ptTemp;
				if( ptTemp.InitWithCifString( sReadBuf ) == false )
				{
					ClearData();
					return false;
				}
				m_lsPointList.Add( ptTemp );
			}
			_CalcBound();
			return true;
		}

		int CDS_Polyline::GetPointCount()
		{
			return m_lsPointList.GetCount();
		}

		CDS_Rect CDS_Polyline::GetBound()
		{
			return m_rcBound;
		}

		CDS_Point CDS_Polyline::GetPoint( int nIndex )
		{
			CDS_Point ptTemp;
			int nCount = m_lsPointList.GetCount();
			if( nIndex >= nCount || nIndex < 0 ) return ptTemp;
			return m_lsPointList[nIndex];
		}

		void CDS_Polyline::SetPoint( int nIndex, CDS_Point ptPoint )
		{
			int nCount = m_lsPointList.GetCount();
			if( nIndex >= nCount || nIndex < 0 ) 
			{
				m_lsPointList.Add( ptPoint );
			}
			else
			{
				m_lsPointList[nIndex] = ptPoint;
			}
			_CalcBound();
		}

		const CDS_Polyline& CDS_Polyline::operator = ( const CDS_Polyline& Source )
		{
			_CopyFrom( Source );
			return Source;
		}

		bool CDS_Polyline::operator == ( const CDS_Polyline& Source )
		{
			return _Match( Source );
		}

		bool CDS_Polyline::operator != ( const CDS_Polyline& Source )
		{
			return !_Match( Source );
		}

		/*
		CDS_Point& CDS_Polyline::operator [] ( int nIndex )
		{
			if( nIndex < 0 || nIndex >= m_lsPointList.GetCount() )
			{
				m_ptPointTemp.SetPoint(0,0);
				return m_ptPointTemp;
			}
			return m_lsPointList[nIndex];
		}
		*/
		
		void CDS_Polyline::_CopyFrom( const CDS_Polyline& Source )
		{
			m_lsPointList.RemoveAll();
			m_bClose = Source.m_bClose;
			int nSourcePointCount = Source.m_lsPointList.GetCount();
			for( int nIndex = 0 ; nIndex < nSourcePointCount ; nIndex ++ )
			{
				m_lsPointList.Add( Source.m_lsPointList[nIndex] );
			}
			m_rcBound = Source.m_rcBound;
		}

		bool CDS_Polyline::_Match( const CDS_Polyline& Source )
		{
			if( m_bClose != Source.m_bClose ) return false;
			int nSourcePointCount = Source.m_lsPointList.GetCount();
			if( nSourcePointCount != m_lsPointList.GetCount() ) return false;
			for( int nIndex = 0 ; nIndex < nSourcePointCount ; nIndex ++ )
			{
				if( m_lsPointList[nIndex] != Source.m_lsPointList[nIndex] ) return false;
			}
			return true;
		}

		void CDS_Polyline::_CalcBound()
		{
			int nPointCount = m_lsPointList.GetCount();
			if( nPointCount <= 0 ) return;
			m_rcBound.InitWithTwoPoint( m_lsPointList[0], m_lsPointList[0] );
			for( int nPointIndex = 1 ; nPointIndex < nPointCount ; nPointIndex ++ )
			{
				m_rcBound.RectExtend( m_lsPointList[nPointIndex] );
			}
		}

		double CDS_Polyline::GetAreaSize(int nUsingDigit)
		{
			double fAreaSize;	

			fAreaSize=0;

			int nPointCount = GetPointCount();
			int nPointIndex;
			for( nPointIndex = 0 ; nPointIndex < nPointCount-1 ; nPointIndex ++ )
			{
				fAreaSize += ( GetPoint(nPointIndex).GetX(nUsingDigit) * GetPoint(nPointIndex + 1).GetY(nUsingDigit) 
								- GetPoint(nPointIndex+1).GetX(nUsingDigit) * GetPoint(nPointIndex).GetY(nUsingDigit) );
			}
			fAreaSize += ( GetPoint(nPointIndex).GetX(nUsingDigit) * GetPoint(0).GetY(nUsingDigit) 
								- GetPoint(0).GetX(nUsingDigit) * GetPoint(nPointIndex).GetY(nUsingDigit) );
			fAreaSize *= 0.5;
		
			return fabs(fAreaSize);
		}
	};
};