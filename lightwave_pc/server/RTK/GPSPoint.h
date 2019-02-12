#pragma once

#include "Shape\\DS_Point.h"

namespace DataType
{
	// #############################################################################
	// GPS���� ��Ÿ���� ������ Ŭ�����̴�.
	class CGPSPoint
	{
	protected:
		double m_fX;
		double m_fY;
		double m_fZ;

		CTime m_timeInputTime;		// �ʼ��� �ƴ�	
									// ���� �������� ���� �� ����� �ƴ�
		int m_nUsingLevel;			// 
	public:
		CGPSPoint(void);
		CGPSPoint(const CGPSPoint& Source);
		~CGPSPoint(void);

		// ##############################################
		// TM��ǥ�� X,Y�� ����Z
		void SetPoint( double m_fX, double m_fY, double m_fZ);		
		double GetX();
		double GetY();
		double GetZ();
		// TM��ǥ�� X,Y�� ����Z
		// ##############################################

		// #############################################
		// �Է¹��� �ð�����
		void SetInputTime( CTime timeInputTime );
		CTime GetInputTime();
		// �Է¹��� �ð�����
		// #############################################

		// #############################################
		// 
		void SetPointUsingLevel( int nLevel );
		int GetPointUsingLevel();
		// 
		// #############################################

		// ##############################################
		// 	������
		virtual const CGPSPoint& operator = (const CGPSPoint& Source );
		virtual bool operator == ( const CGPSPoint& Source );
		virtual bool operator != ( const CGPSPoint& Source );

		virtual ShapeType::CDS_Point operator = ( ShapeType::CDS_Point ptSource );
		virtual operator ShapeType::CDS_Point ();

		// ����ȯ ����
		void SetPoint( ShapeType::CDS_Point ptSource );
		ShapeType::CDS_Point ToDSPoint();
		CString ToString();

		// ##############################################
		// 	�����Լ�
	protected:
		void _InitValue();
		void _CopyFrom( const CGPSPoint& Source );
		bool _Match( const CGPSPoint& Source );

	};
};

