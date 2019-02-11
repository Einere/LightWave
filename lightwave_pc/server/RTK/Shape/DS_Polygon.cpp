#include "StdAfx.h"
#include "DS_Polygon.h"

namespace DataType
{
	namespace ShapeType
	{
		CDS_Polygon::CDS_Polygon(void)
		{
		}

		CDS_Polygon::CDS_Polygon(const CDS_Polygon& Source)
		{
			_CopyFrom( Source );
		}

		CDS_Polygon::~CDS_Polygon(void)
		{
		}

		bool CDS_Polygon::InitWithCifStringArray(CArray<CString>& lsCifStringList,int& nCoordStartIndex )
		{
			if( lsCifStringList[nCoordStartIndex] == "" ) return false;
			int nPolyLineCount = atoi( lsCifStringList[nCoordStartIndex] );
			if( nPolyLineCount <= 0 ) return false;
			CArray<int> lsPointCount;
			for( int nPointCountIndex = 0 ; nPointCountIndex < nPolyLineCount ; nPointCountIndex ++ )
			{
				CString sReadBuf = lsCifStringList[ nCoordStartIndex + 1 + nPointCountIndex ];
				int nPointCount = atoi( sReadBuf );
				if( nPointCount <= 0 ) 
				{
					nCoordStartIndex = nCoordStartIndex  + 1 + nPointCountIndex;
					return false;
				}
				lsPointCount.Add( nPointCount );
			}
			// 외각선
			CDS_Polyline plOutline;
			int nPointIndex = nCoordStartIndex + nPolyLineCount + 1;
			if( plOutline.InitWithCifStringArray( lsCifStringList, nPointIndex, lsPointCount[0] ) == false )
			{
				nCoordStartIndex = nPointIndex;
				return false;
			}
			m_plOutline = plOutline;

			// 홀
			for( int nPlIndex = 1 ; nPlIndex < nPolyLineCount ; nPlIndex ++ )
			{
				CDS_Polyline plHoleTemp;
				if( plOutline.InitWithCifStringArray( lsCifStringList, nPointIndex, lsPointCount[nPlIndex] ) == false )
				{
					nCoordStartIndex = nPointIndex;
					return false;
				}
				m_lsplInsideHole.Add( plHoleTemp );
			}
			nCoordStartIndex = nPointIndex;
			return true;
		}

		bool CDS_Polygon::InitWithCifFile( CStdioFile& flCifFile )
		{
			CString sReadBuf;
			if( flCifFile.ReadString( sReadBuf ) == false ) return false;
			sReadBuf = sReadBuf.Trim();
			int nPolyLineCount = atoi( sReadBuf );
			if( nPolyLineCount <= 0 ) return false;

			CArray<int> lsPointCount;
			for( int nPointCountIndex = 0 ; nPointCountIndex < nPolyLineCount ; nPointCountIndex ++ )
			{
				flCifFile.ReadString( sReadBuf );
				sReadBuf = sReadBuf.Trim();
				int nPointCount = atoi( sReadBuf );
				if( nPointCount <= 0 ) 
				{
					return false;
				}
				lsPointCount.Add( nPointCount );
			}
			// 외각선
			CDS_Polyline plOutline;
			if( plOutline.InitWithCifFile( flCifFile, lsPointCount[0] ) == false )
			{
				return false;
			}
			m_plOutline = plOutline;

			// 홀
			for( int nPlIndex = 1 ; nPlIndex < nPolyLineCount ; nPlIndex ++ )
			{
				CDS_Polyline plHoleTemp;
				if( plHoleTemp.InitWithCifFile( flCifFile, lsPointCount[nPlIndex] ) == false )
				{
					return false;
				}
				m_lsplInsideHole.Add( plHoleTemp );
			}
			return true;
		}

		CDS_Polyline* CDS_Polygon::GetPolyline( int nIndex )
		{
			if( (nIndex < 0) || ( nIndex - 1 >= m_lsplInsideHole.GetCount() ) ) return NULL;
			if( nIndex == 0 ) return &m_plOutline;
			return &( m_lsplInsideHole[nIndex-1] );
		}

		int CDS_Polygon::GetPolylineCount()
		{
			return m_lsplInsideHole.GetCount() + 1;
		}

		CDS_Rect CDS_Polygon::GetBound()
		{
			return m_plOutline.GetBound();
		}

		double CDS_Polygon::GetAreaSize( int nUsingDigit )
		{
			double fOutLineAreaSize = m_plOutline.GetAreaSize(nUsingDigit);
			double fSumHallAreaSize = 0.0;
			int nHoleCount = m_lsplInsideHole.GetCount();
			for( int nHoleIndex = 0 ; nHoleIndex < nHoleCount ; nHoleIndex ++ )
			{
				fSumHallAreaSize += m_lsplInsideHole[nHoleIndex].GetAreaSize(nUsingDigit);
			}
			return fOutLineAreaSize - fSumHallAreaSize;
		}

		const CDS_Polygon& CDS_Polygon::operator = ( const CDS_Polygon& Source )
		{
			_CopyFrom( Source );
			return Source;
		}
		
		bool CDS_Polygon::operator == ( const CDS_Polygon& Source )
		{
			return _Match( Source );
		}

		bool CDS_Polygon::operator != ( const CDS_Polygon& Source )
		{
			return !_Match( Source );
		}

		void CDS_Polygon::_CopyFrom( const CDS_Polygon& Source )
		{
			m_lsplInsideHole.RemoveAll();
			m_plOutline = Source.m_plOutline;
			int nHoleCount = Source.m_lsplInsideHole.GetCount();
			for( int nIndex = 0 ; nIndex < nHoleCount ; nIndex ++ )
			{
				m_lsplInsideHole.Add( Source.m_lsplInsideHole[nIndex] );
			}
		}

		bool CDS_Polygon::_Match( const CDS_Polygon& Source )
		{
			// 홀필지를 비교할때 인덱스는 중요하지 않기때문에 같은 홀이 잇는지 다른 인덱스 값도 확인해야하지만.
			// 이번에는 인덱스 순서대로 비교하도록 그대로 두었다.
			if( m_plOutline != Source.m_plOutline ) return false;
			int nHoleCount = Source.m_lsplInsideHole.GetCount();
			if( nHoleCount != m_lsplInsideHole.GetCount() ) return false;
			for( int nIndex = 0 ; nIndex < nHoleCount ; nIndex ++ )
			{
				if( m_lsplInsideHole[nIndex] != Source.m_lsplInsideHole[nIndex] ) return false;
			}
			return true;
		}
	};
};