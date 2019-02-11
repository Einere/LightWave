#pragma once

#include "DS_Shape.h"
#include "DS_Polyline.h"

namespace DataType
{
	namespace ShapeType
	{
		// #############################################################################
		// 폴리곤을 나타내는 도형관련 데이터 클래스이다.
		class CDS_Polygon : public CDS_Shape
		{
		protected:
			CDS_Polyline m_plOutline;						// 외곽 폴리라인
			CArray<CDS_Polyline> m_lsplInsideHole;			// 내부 홀 폴리라인리스트

		public:
			// ======================================================
			// 생성자 / 소멸자
			CDS_Polygon(void);
			CDS_Polygon( const CDS_Polygon& Source );
			~CDS_Polygon(void);

			// ======================================================
			// 폴리곤 설정및 값 가져오기
			bool InitWithCifStringArray(CArray<CString>& lsCifStringList,int& nCoordStartIndex );
															// CIF에서 읽어온 문자열로 폴리곤 초기화 ( 속도관계상 사용 안함 )
			bool InitWithCifFile( CStdioFile& flCifFile );	// CIF파일에서 읽어와서 폴리곤 초기화
			CDS_Polyline* GetPolyline( int nIndex );		// 인덱스 번째의 폴리라인 가져오기
			int GetPolylineCount();							// 전체 폴리라인 갯수

			// ======================================================
			// 폴리곤의 부수적 정보 관련
			CDS_Rect GetBound();							// 폴리곤을 포함하는 최소 사각형
			double GetAreaSize(int nUsingDigit = -1);		// 폴리곤의 면적

			// ======================================================
			// 연산자
			virtual const CDS_Polygon& operator = ( const CDS_Polygon& Source );
			virtual bool operator == ( const CDS_Polygon& Source );
			virtual bool operator != ( const CDS_Polygon& Source );
//			virtual CDS_Polyline* operator [] ( int nIndex );

			// ======================================================
			// 

			// ======================================================
			// 내부 함수
		protected:
			void _CopyFrom( const CDS_Polygon& Source );
			bool _Match( const CDS_Polygon& Source );
		};
	};
};