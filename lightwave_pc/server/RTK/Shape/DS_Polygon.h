#pragma once

#include "DS_Shape.h"
#include "DS_Polyline.h"

namespace DataType
{
	namespace ShapeType
	{
		// #############################################################################
		// �������� ��Ÿ���� �������� ������ Ŭ�����̴�.
		class CDS_Polygon : public CDS_Shape
		{
		protected:
			CDS_Polyline m_plOutline;						// �ܰ� ��������
			CArray<CDS_Polyline> m_lsplInsideHole;			// ���� Ȧ �������θ���Ʈ

		public:
			// ======================================================
			// ������ / �Ҹ���
			CDS_Polygon(void);
			CDS_Polygon( const CDS_Polygon& Source );
			~CDS_Polygon(void);

			// ======================================================
			// ������ ������ �� ��������
			bool InitWithCifStringArray(CArray<CString>& lsCifStringList,int& nCoordStartIndex );
															// CIF���� �о�� ���ڿ��� ������ �ʱ�ȭ ( �ӵ������ ��� ���� )
			bool InitWithCifFile( CStdioFile& flCifFile );	// CIF���Ͽ��� �о�ͼ� ������ �ʱ�ȭ
			CDS_Polyline* GetPolyline( int nIndex );		// �ε��� ��°�� �������� ��������
			int GetPolylineCount();							// ��ü �������� ����

			// ======================================================
			// �������� �μ��� ���� ����
			CDS_Rect GetBound();							// �������� �����ϴ� �ּ� �簢��
			double GetAreaSize(int nUsingDigit = -1);		// �������� ����

			// ======================================================
			// ������
			virtual const CDS_Polygon& operator = ( const CDS_Polygon& Source );
			virtual bool operator == ( const CDS_Polygon& Source );
			virtual bool operator != ( const CDS_Polygon& Source );
//			virtual CDS_Polyline* operator [] ( int nIndex );

			// ======================================================
			// 

			// ======================================================
			// ���� �Լ�
		protected:
			void _CopyFrom( const CDS_Polygon& Source );
			bool _Match( const CDS_Polygon& Source );
		};
	};
};