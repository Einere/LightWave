#pragma once



namespace DataType
{
	namespace ShapeType
	{
		class CDS_Point;

		// #############################################################################
		// �������� ������ Ŭ������ �θ�Ŭ�����̴�.
		class CDS_Shape
		{
		protected:

		public:
			CDS_Shape();
			virtual ~CDS_Shape();

			virtual void MoveEnt( CDS_Point ptOffset );		// ���� �̵� ���� �Լ�
		};
	};
};