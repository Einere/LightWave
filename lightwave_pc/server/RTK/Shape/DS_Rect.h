#pragma once

#include "DS_Shape.h"
#include "DS_Point.h"

namespace DataType
{
	namespace ShapeType
	{
		// #############################################################################
		// �簢���� ��Ÿ���� �������� ������ Ŭ�����̴�.
		class CDS_Rect : public CDS_Shape
		{
		protected:
			double m_fLeft;
			double m_fRight;
			double m_fTop;
			double m_fBottom;

		public:
			// ======================================================
			// ������ / �Ҹ���
			CDS_Rect(void);
			CDS_Rect(const CDS_Rect& rcSource );
			~CDS_Rect(void);

			// ======================================================
			// �簢�� ������ �� ��������
			//void InitWithLeftBottomAndRightTop( CDS_Point ptLeftBottom , CDS_Point ptRightTop );
			bool InitWithTwoPoint( CDS_Point ptTemp1, CDS_Point ptTemp2 );
															// �������� �簢�� ����
			CDS_Point GetLeftTop();							// �簢���� ������ �� ��������
			CDS_Point GetRightTop();						// �簢���� �������� �� ��������
			CDS_Point GetLeftBottom();						// �簢���� ���ʾƷ� �� ��������
			CDS_Point GetRightBottom();						// �簢���� �������Ʒ� �� ��������
			CDS_Point GetCenter();							// �簢���� ��� �� ��������
			double GetAreaSize();							// �簢���� ���� ��������
			double GetWidth();								// �簢���� �ʺ� ��������
			double GetHeight();								// �簢���� ���� ��������
			bool RectExtend( CDS_Point ptTemp );			// ������ �簢�� Ȯ��

			// ======================================================
			// ������
			virtual const CDS_Rect& operator = ( const CDS_Rect& rcSource );
			virtual bool operator == ( const CDS_Rect& rcSource );
			virtual bool operator != ( const CDS_Rect& rcSource );

			// ======================================================
			// ���� �Լ�
		protected:
			void _CopyFrom( const CDS_Rect& rcSource );
			bool _Match( const CDS_Rect& rcSource );
			
		};
	};
};

