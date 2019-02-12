#pragma once

#include "DS_Shape.h"
#include "DS_Point.h"

namespace DataType
{
	namespace ShapeType
	{
		// #############################################################################
		// 사각형을 나타내는 도형관련 데이터 클래스이다.
		class CDS_Rect : public CDS_Shape
		{
		protected:
			double m_fLeft;
			double m_fRight;
			double m_fTop;
			double m_fBottom;

		public:
			// ======================================================
			// 생성자 / 소멸자
			CDS_Rect(void);
			CDS_Rect(const CDS_Rect& rcSource );
			~CDS_Rect(void);

			// ======================================================
			// 사각형 설정및 값 가져오기
			//void InitWithLeftBottomAndRightTop( CDS_Point ptLeftBottom , CDS_Point ptRightTop );
			bool InitWithTwoPoint( CDS_Point ptTemp1, CDS_Point ptTemp2 );
															// 두점으로 사각형 설정
			CDS_Point GetLeftTop();							// 사각형의 왼쪽위 점 가져오기
			CDS_Point GetRightTop();						// 사각형의 오른쪽위 점 가져오기
			CDS_Point GetLeftBottom();						// 사각형의 왼쪽아래 점 가져오기
			CDS_Point GetRightBottom();						// 사각형의 오른족아래 점 가져오기
			CDS_Point GetCenter();							// 사각형의 가운데 점 가져오기
			double GetAreaSize();							// 사각형의 넓이 가져오기
			double GetWidth();								// 사각형의 너비 가져오기
			double GetHeight();								// 사각형의 높이 가져오기
			bool RectExtend( CDS_Point ptTemp );			// 점으로 사각형 확장

			// ======================================================
			// 연산자
			virtual const CDS_Rect& operator = ( const CDS_Rect& rcSource );
			virtual bool operator == ( const CDS_Rect& rcSource );
			virtual bool operator != ( const CDS_Rect& rcSource );

			// ======================================================
			// 내부 함수
		protected:
			void _CopyFrom( const CDS_Rect& rcSource );
			bool _Match( const CDS_Rect& rcSource );
			
		};
	};
};

