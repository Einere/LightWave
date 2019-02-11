#pragma once

#include "DS_Shape.h"

namespace DataType
{
	namespace ShapeType
	{
		// #############################################################################
		// 점을 나타내는 도형관련 데이터 클래스이다.
		class CDS_Point : public CDS_Shape
		{
		protected:
			double m_fX;								// X좌표
			double m_fY;								// Y좌표

		public:
			// ======================================================
			// 생성자 / 소멸자
			CDS_Point(void);
			CDS_Point( double fX, double fY );
			CDS_Point(const CDS_Point& Source);
			~CDS_Point(void);

			// ======================================================
			// 점 설정및 값 가져오기
			void SetPoint( double fX, double fY );		// 점 설정
			double GetX(int nUsingDigit = -1);			// X좌표 가져오기 ( 유효 소수점 수에 따라 값을 잘라준다. )
			double GetY(int nUsingDigit = -1);			// Y좌표 가져오기 ( 유효 소수점 수에 따라 값을 잘라준다. )

			bool InitWithCifString( CString sPointCoord );
														// CIF에 포함된 문자열로 점 초기화

			// ======================================================
			// 연산자
			virtual const CDS_Point& operator = ( const CDS_Point& Source );
			virtual bool operator == ( const CDS_Point& Source );
			virtual bool operator != ( const CDS_Point& Source );

			// ======================================================
			// 
			virtual void MoveEnt( CDS_Point ptOffset );	// 도형 이동
		
			// ======================================================
			// 내부 함수
		protected:
			void _CopyFrom( const CDS_Point& Source );
			bool _Match( const CDS_Point& Source );

		
			// ======================================================
			// 점관련 지원 함수들
		public:
			static double GetDistOfInsideTwoPoint( CDS_Point ptPoint1, CDS_Point ptPoint2 );
															// 두점 사이의 거리이다.
		};
	};
};