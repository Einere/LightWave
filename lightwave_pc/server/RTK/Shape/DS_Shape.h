#pragma once



namespace DataType
{
	namespace ShapeType
	{
		class CDS_Point;

		// #############################################################################
		// 도형관련 데이터 클래스의 부모클래스이다.
		class CDS_Shape
		{
		protected:

		public:
			CDS_Shape();
			virtual ~CDS_Shape();

			virtual void MoveEnt( CDS_Point ptOffset );		// 도형 이동 관련 함수
		};
	};
};