#pragma once

#include "DS_Shape.h"
#include "DS_Point.h"
#include "..\\Angle.h"

namespace DataType
{
	namespace ShapeType
	{
		// #############################################################################
		// 라인을 나타내는 도형관련 데이터 클래스이다.
		class CDS_Line : public CDS_Shape
		{
		public:
			CDS_Point m_ptFirstPoint;							// 첫번째 점
			CDS_Point m_ptSecondPoint;							// 두번째 점

		public:
			// ======================================================
			// 생성자 / 소멸자
			CDS_Line(void);
			CDS_Line( CDS_Point ptPoint1, CDS_Point ptPoint2 );
			CDS_Line( const CDS_Line& lnSource );
			virtual ~CDS_Line();

//			CDS_Point GetFirstPoint();
//			CDS_Point GetSecondPoint();

			// ======================================================
			// 라인 설정
			void SetLine( CDS_Point ptPoint1, CDS_Point ptPoint2 );
			void SetLine( double fX1, double fY1, double fX2, double fY2 );

			// ======================================================
			// 라인의 부수적 정보 관련
			CAngle GetAngle();				// 이 선의 X축으로부터의 각도 
			CAngle GetAzimuth();			// Azimuth는 방위각 임으로 Y축으로 부터 시계방향으로의 각도를 의미한다.

			double GetDist();				// 라인의 길이도

			// ======================================================
			// 연산자
			virtual const CDS_Line& operator = ( const CDS_Line& lnSource );
			virtual bool operator == ( const CDS_Line& lnSource );
			virtual bool operator != ( const CDS_Line& lnSource );

			// ======================================================
			// 
			virtual void MoveEnt( CDS_Point ptOffset );	// 도형 이동
		
			// ======================================================
			// 내부 함수
		protected:
			void _CopyFrom( const CDS_Line& lnSource );
			bool _Match( const CDS_Line& lnSource );

		

			// ======================================================
			// 라인관련 지원 함수들
		public:
			static CAngle GetInsideAngleOfTwoLine( CDS_Line lnLine1, CDS_Line lnLine2 );
											// 선1에서 부터 선 2으로의 반시계 방향으로의 각도이다. 

			static CDS_Line CalLineOfAngleAndDist( CAngle aRotationAngle, double fDist );
											// 길이가 fDist인 X축으로 부터 Angle만큼 회전되어있는 선을 구한다.
		};
	};
};
