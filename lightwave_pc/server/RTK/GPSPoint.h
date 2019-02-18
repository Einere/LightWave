#pragma once

#include "Shape\\DS_Point.h"

namespace DataType
{
	// #############################################################################
	// GPS점을 나타내는 데이터 클래스이다.
	class CGPSPoint
	{
	protected:
		double m_fX;
		double m_fY;
		double m_fZ;

		CTime m_timeInputTime;		// 필수가 아님	
									// 같은 값인지에 대한 비교 대상이 아님
		int m_nUsingLevel;			// 
	public:
		CGPSPoint(void);
		CGPSPoint(const CGPSPoint& Source);
		~CGPSPoint(void);

		// ##############################################
		// TM좌표계 X,Y에 고도값Z
		void SetPoint( double m_fX, double m_fY, double m_fZ);		
		double GetX();
		double GetY();
		double GetZ();
		// TM좌표계 X,Y에 고도값Z
		// ##############################################

		// #############################################
		// 입력받은 시간정보
		void SetInputTime( CTime timeInputTime );
		CTime GetInputTime();
		// 입력받은 시간정보
		// #############################################

		// #############################################
		// 
		void SetPointUsingLevel( int nLevel );
		int GetPointUsingLevel();
		// 
		// #############################################

		// ##############################################
		// 	연산자
		virtual const CGPSPoint& operator = (const CGPSPoint& Source );
		virtual bool operator == ( const CGPSPoint& Source );
		virtual bool operator != ( const CGPSPoint& Source );

		virtual ShapeType::CDS_Point operator = ( ShapeType::CDS_Point ptSource );
		virtual operator ShapeType::CDS_Point ();

		// 형변환 지원
		void SetPoint( ShapeType::CDS_Point ptSource );
		ShapeType::CDS_Point ToDSPoint();
		CString ToString();

		// ##############################################
		// 	내부함수
	protected:
		void _InitValue();
		void _CopyFrom( const CGPSPoint& Source );
		bool _Match( const CGPSPoint& Source );

	};
};

