#pragma once


namespace DataType
{
	// #############################################################################
	// ������ ��Ÿ���� ������ Ŭ����
	class CAngle
	{
	protected:	
		// ========================================================================
		// �������		
		double	m_fSecond;								// ��
		bool	m_bMode;								// 0~360���� ����		( ������� ���� )											 
														// (true-����, false-����)
														// default: false
	public:
		// ========================================================================
		// ������
		CAngle(void);									// 0���� ������ ����	
		CAngle(double fDegree);						// ���� �Է¹޾Ƽ� ������ ����
		CAngle(int nDeg,int nMin,double fSec);			// �����ʸ� �Է¹޾Ƽ� ������ ����		
		CAngle(const CAngle& aSource );					// ���������
		~CAngle(void);


		// ========================================================================
		// ������ ��������
//		void SetMode(bool bMode );						// ��� ����
//		bool GetMode();									// ��� ��������

		int GetDegree();								// ���� ��������
		int GetMinute();								// �а� ��������
		double GetSecond();								// �ʰ� ��������

		double ToDegree();								// �������� ���� ȯ���Ͽ� ��������
		double ToMinute();								// �а����� ���� ȯ���Ͽ� ��������
		double ToSecond();								// �ʰ����� ���� ȯ���Ͽ� ��������

		double ToRadian();								// ���� ������ ��������
		CString ToString();								// ������ ��Ʋ�������� ��ȯ

		void SetAngle( double fSecond );				// �ʰ����� ���� ����
		void SetAngle( int nDeg, int nMin, double fSec );// ��, ��, �ʰ����� ���� ����
		void SetAngleFromRadian( double fRadian );		// ���� ������ ������ ����
		void SetAngleFromMachineInt( CString sValue, int nBaseValue = 10000);
														// ���� ���� ���� ������ nBaseValue�� 360������ �������� �ȴ�. 

		CAngle GetRevisionAngle();

		// ========================================================================
		// ������
		virtual const CAngle& operator = ( const CAngle& aSource );		// ���Կ�����	
		virtual CAngle operator + ( const CAngle& aSource );
		virtual CAngle operator += ( const CAngle& aSource );
		virtual CAngle operator - ( const CAngle& aSource );
		virtual CAngle operator -= ( const CAngle& aSource );

		virtual bool operator == ( const CAngle& aSource );				// �񱳿�����
		virtual bool operator != ( const CAngle& aSource );				
		virtual bool operator < ( const CAngle& aSource );
		virtual bool operator > ( const CAngle& aSource );
		virtual bool operator <= ( const CAngle& aSource );
		virtual bool operator >= ( const CAngle& aSource );

		// double ���¿� ����
		virtual double operator = ( double fDegree );						// �� �Է�

	protected:
		// ========================================================================
		// �����Լ�
		void _Init();													// �ʱ�ȭ
		void _CopyFrom( const CAngle& aSource );						// ����
		int _Compare( const CAngle& aSource );							// �� ( < : -1 / == : 0 / > : 1 )
		void _Add( const CAngle& aSource );								// aSource ��ŭ ���Ѵ�.
		void _Sub( const CAngle& aSource );								// aSource��ŭ ����.

		void _CalcIn360();												// 0~360�� ������ ������ ����
	};
};