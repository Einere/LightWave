#pragma once

#include "DS_Shape.h"

namespace DataType
{
	namespace ShapeType
	{
		// #############################################################################
		// ���� ��Ÿ���� �������� ������ Ŭ�����̴�.
		class CDS_Point : public CDS_Shape
		{
		protected:
			double m_fX;								// X��ǥ
			double m_fY;								// Y��ǥ

		public:
			// ======================================================
			// ������ / �Ҹ���
			CDS_Point(void);
			CDS_Point( double fX, double fY );
			CDS_Point(const CDS_Point& Source);
			~CDS_Point(void);

			// ======================================================
			// �� ������ �� ��������
			void SetPoint( double fX, double fY );		// �� ����
			double GetX(int nUsingDigit = -1);			// X��ǥ �������� ( ��ȿ �Ҽ��� ���� ���� ���� �߶��ش�. )
			double GetY(int nUsingDigit = -1);			// Y��ǥ �������� ( ��ȿ �Ҽ��� ���� ���� ���� �߶��ش�. )

			bool InitWithCifString( CString sPointCoord );
														// CIF�� ���Ե� ���ڿ��� �� �ʱ�ȭ

			// ======================================================
			// ������
			virtual const CDS_Point& operator = ( const CDS_Point& Source );
			virtual bool operator == ( const CDS_Point& Source );
			virtual bool operator != ( const CDS_Point& Source );

			// ======================================================
			// 
			virtual void MoveEnt( CDS_Point ptOffset );	// ���� �̵�
		
			// ======================================================
			// ���� �Լ�
		protected:
			void _CopyFrom( const CDS_Point& Source );
			bool _Match( const CDS_Point& Source );

		
			// ======================================================
			// ������ ���� �Լ���
		public:
			static double GetDistOfInsideTwoPoint( CDS_Point ptPoint1, CDS_Point ptPoint2 );
															// ���� ������ �Ÿ��̴�.
		};
	};
};