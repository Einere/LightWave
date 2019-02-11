#pragma once

#include "DS_Shape.h"
#include "DS_Point.h"
#include "..\\Angle.h"

namespace DataType
{
	namespace ShapeType
	{
		// #############################################################################
		// ������ ��Ÿ���� �������� ������ Ŭ�����̴�.
		class CDS_Line : public CDS_Shape
		{
		public:
			CDS_Point m_ptFirstPoint;							// ù��° ��
			CDS_Point m_ptSecondPoint;							// �ι�° ��

		public:
			// ======================================================
			// ������ / �Ҹ���
			CDS_Line(void);
			CDS_Line( CDS_Point ptPoint1, CDS_Point ptPoint2 );
			CDS_Line( const CDS_Line& lnSource );
			virtual ~CDS_Line();

//			CDS_Point GetFirstPoint();
//			CDS_Point GetSecondPoint();

			// ======================================================
			// ���� ����
			void SetLine( CDS_Point ptPoint1, CDS_Point ptPoint2 );
			void SetLine( double fX1, double fY1, double fX2, double fY2 );

			// ======================================================
			// ������ �μ��� ���� ����
			CAngle GetAngle();				// �� ���� X�����κ����� ���� 
			CAngle GetAzimuth();			// Azimuth�� ������ ������ Y������ ���� �ð���������� ������ �ǹ��Ѵ�.

			double GetDist();				// ������ ���̵�

			// ======================================================
			// ������
			virtual const CDS_Line& operator = ( const CDS_Line& lnSource );
			virtual bool operator == ( const CDS_Line& lnSource );
			virtual bool operator != ( const CDS_Line& lnSource );

			// ======================================================
			// 
			virtual void MoveEnt( CDS_Point ptOffset );	// ���� �̵�
		
			// ======================================================
			// ���� �Լ�
		protected:
			void _CopyFrom( const CDS_Line& lnSource );
			bool _Match( const CDS_Line& lnSource );

		

			// ======================================================
			// ���ΰ��� ���� �Լ���
		public:
			static CAngle GetInsideAngleOfTwoLine( CDS_Line lnLine1, CDS_Line lnLine2 );
											// ��1���� ���� �� 2������ �ݽð� ���������� �����̴�. 

			static CDS_Line CalLineOfAngleAndDist( CAngle aRotationAngle, double fDist );
											// ���̰� fDist�� X������ ���� Angle��ŭ ȸ���Ǿ��ִ� ���� ���Ѵ�.
		};
	};
};
