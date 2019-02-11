#pragma once

#include "DS_Shape.h"
#include "DS_Point.h"
#include "DS_Rect.h"

namespace DataType
{
	namespace ShapeType
	{
		// #############################################################################
		// ���������� ��Ÿ���� �������� ������ Ŭ�����̴�.
		class CDS_Polyline : public CDS_Shape
		{
		protected:
			CArray<CDS_Point> m_lsPointList;	// ���������� �����ϴ� ������ ����Ʈ
			bool m_bClose;						// ���������� �м� ���� ( ����� ���� �׻� true )
			CDS_Point m_ptPointTemp;			// ������ �ʽ��ϴ�.
			CDS_Rect m_rcBound;					// �������� �ٲ� ����

		public:
			// ======================================================
			// ������ / �Ҹ���
			CDS_Polyline(void);
			CDS_Polyline( const CDS_Polyline& Source );
			~CDS_Polyline(void);

			void ClearData();

			// ======================================================
			// �������� ������ �� ��������
			bool InitWithCifStringArray(CArray<CString>& lsCifStringList,int& nCoordStartIndex,int nCoordCount );
															// CIF���� �о�� ���ڿ��� �������� �ʱ�ȭ ( �ӵ������ ��� ���� )
			bool InitWithCifFile( CStdioFile& flCifFile, int nPointCount );
															// CIF���Ͽ��� �о�ͼ� �������� �ʱ�ȭ
			
			int GetPointCount();							// ��ü �� ���� ��������
			CDS_Point GetPoint( int nIndex );				// �ε��� ��°�� �� ��������
			void SetPoint( int nIndex, CDS_Point ptPoint );	// �ε��� ��°�� �� ����

			// ======================================================
			// �������� �μ��� ���� ����
			CDS_Rect GetBound();							// �ܰ��� �̷�� �簢�� ��������
			double GetAreaSize(int nUsingDigit = -1);		// ���������� ����
			
			// ======================================================
			// ������
			virtual const CDS_Polyline& operator = ( const CDS_Polyline& Source );
			virtual bool operator == ( const CDS_Polyline& Source );
			virtual bool operator != ( const CDS_Polyline& Source );
//			virtual CDS_Point& operator [] ( int nIndex );


			
			// ======================================================
			// 

			// ======================================================
			// ���� �Լ�
		protected:
			void _CopyFrom( const CDS_Polyline& Source );
			bool _Match( const CDS_Polyline& Source );
			void _CalcBound();
		};

	};
};