#pragma once

#include "DS_Shape.h"
#include "DS_Point.h"
#include "DS_Rect.h"

namespace DataType
{
	namespace ShapeType
	{
		// #############################################################################
		// 폴리라인을 나타내는 도형관련 데이터 클래스이다.
		class CDS_Polyline : public CDS_Shape
		{
		protected:
			CArray<CDS_Point> m_lsPointList;	// 폴리라인을 구성하는 점드의 리스트
			bool m_bClose;						// 폴리라인의 패쇄 여부 ( 현재는 거의 항상 true )
			CDS_Point m_ptPointTemp;			// 사용되지 않습니다.
			CDS_Rect m_rcBound;					// 점정보가 바뀔때 갱신

		public:
			// ======================================================
			// 생성자 / 소멸자
			CDS_Polyline(void);
			CDS_Polyline( const CDS_Polyline& Source );
			~CDS_Polyline(void);

			void ClearData();

			// ======================================================
			// 폴리라인 설정및 값 가져오기
			bool InitWithCifStringArray(CArray<CString>& lsCifStringList,int& nCoordStartIndex,int nCoordCount );
															// CIF에서 읽어온 문자열로 폴리라인 초기화 ( 속도관계상 사용 안함 )
			bool InitWithCifFile( CStdioFile& flCifFile, int nPointCount );
															// CIF파일에서 읽어와서 폴리라인 초기화
			
			int GetPointCount();							// 전체 점 갯수 가져오기
			CDS_Point GetPoint( int nIndex );				// 인덱스 번째의 점 가져오기
			void SetPoint( int nIndex, CDS_Point ptPoint );	// 인덱스 번째의 점 설정

			// ======================================================
			// 폴리곤의 부수적 정보 관련
			CDS_Rect GetBound();							// 외곽을 이루는 사각형 가져오기
			double GetAreaSize(int nUsingDigit = -1);		// 폴리라인의 면적
			
			// ======================================================
			// 연산자
			virtual const CDS_Polyline& operator = ( const CDS_Polyline& Source );
			virtual bool operator == ( const CDS_Polyline& Source );
			virtual bool operator != ( const CDS_Polyline& Source );
//			virtual CDS_Point& operator [] ( int nIndex );


			
			// ======================================================
			// 

			// ======================================================
			// 내부 함수
		protected:
			void _CopyFrom( const CDS_Polyline& Source );
			bool _Match( const CDS_Polyline& Source );
			void _CalcBound();
		};

	};
};