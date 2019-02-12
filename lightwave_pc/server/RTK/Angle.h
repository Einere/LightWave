#pragma once


namespace DataType
{
	// #############################################################################
	// 각도를 나타내는 데이터 클래스
	class CAngle
	{
	protected:	
		// ========================================================================
		// 멤버변수		
		double	m_fSecond;								// 초
		bool	m_bMode;								// 0~360도로 제한		( 사용하지 않음 )											 
														// (true-제한, false-해제)
														// default: false
	public:
		// ========================================================================
		// 생성자
		CAngle(void);									// 0도의 각도를 생성	
		CAngle(double fDegree);						// 도를 입력받아서 각도를 생성
		CAngle(int nDeg,int nMin,double fSec);			// 도분초를 입력받아서 각도를 생성		
		CAngle(const CAngle& aSource );					// 복사생성자
		~CAngle(void);


		// ========================================================================
		// 설정및 가져오기
//		void SetMode(bool bMode );						// 모드 설정
//		bool GetMode();									// 모드 가져오기

		int GetDegree();								// 도값 가져오기
		int GetMinute();								// 분값 가져오기
		double GetSecond();								// 초값 가져오기

		double ToDegree();								// 도값으로 값을 환산하여 가져오기
		double ToMinute();								// 분값으로 값을 환산하여 가져오기
		double ToSecond();								// 초값으로 값을 환산하여 가져오기

		double ToRadian();								// 라디안 값으로 가져오기
		CString ToString();								// 각도를 스틀링값으로 변환

		void SetAngle( double fSecond );				// 초값으로 값을 세팅
		void SetAngle( int nDeg, int nMin, double fSec );// 도, 분, 초값으로 값을 세팅
		void SetAngleFromRadian( double fRadian );		// 라디안 값으로 각도를 세팅
		void SetAngleFromMachineInt( CString sValue, int nBaseValue = 10000);
														// 기계로 부터 값을 받으며 nBaseValue가 360도임을 기준으로 된다. 

		CAngle GetRevisionAngle();

		// ========================================================================
		// 연산자
		virtual const CAngle& operator = ( const CAngle& aSource );		// 대입연산자	
		virtual CAngle operator + ( const CAngle& aSource );
		virtual CAngle operator += ( const CAngle& aSource );
		virtual CAngle operator - ( const CAngle& aSource );
		virtual CAngle operator -= ( const CAngle& aSource );

		virtual bool operator == ( const CAngle& aSource );				// 비교연산자
		virtual bool operator != ( const CAngle& aSource );				
		virtual bool operator < ( const CAngle& aSource );
		virtual bool operator > ( const CAngle& aSource );
		virtual bool operator <= ( const CAngle& aSource );
		virtual bool operator >= ( const CAngle& aSource );

		// double 형태와 관련
		virtual double operator = ( double fDegree );						// 도 입력

	protected:
		// ========================================================================
		// 내부함수
		void _Init();													// 초기화
		void _CopyFrom( const CAngle& aSource );						// 복사
		int _Compare( const CAngle& aSource );							// 비교 ( < : -1 / == : 0 / > : 1 )
		void _Add( const CAngle& aSource );								// aSource 만큼 더한다.
		void _Sub( const CAngle& aSource );								// aSource만큼 뺀다.

		void _CalcIn360();												// 0~360도 사이의 각도로 보정
	};
};