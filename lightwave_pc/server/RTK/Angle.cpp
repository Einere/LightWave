#include "StdAfx.h"
#include "Angle.h"
#include <valarray>




namespace DataType
{
	// #############################################################################
	// 생성자

	////////////////////////////////////////////////////////////////////////////
	// 0도의 각도를 생성
	CAngle::CAngle(void)
	{
		_Init();
	}

	////////////////////////////////////////////////////////////////////////////
	// 초를 입력받아서 각도를 생성
	CAngle::CAngle(double fDegree)
	{
		_Init();
		double fSec = fDegree * 3600;
		SetAngle( fSec );
	}

	////////////////////////////////////////////////////////////////////////////
	// 도분초를 입력받아서 각도를 생성		
	CAngle::CAngle(int nDeg,int nMin,double fSec)
	{
		_Init();
		SetAngle( nDeg, nMin, fSec );
	}

	////////////////////////////////////////////////////////////////////////////
	// 복사생성자
	CAngle::CAngle(const CAngle& aSource )
	{
		_Init();
		_CopyFrom( aSource );
	}

	////////////////////////////////////////////////////////////////////////////
	// 소멸자
	CAngle::~CAngle(void)
	{
	
	}



	// #############################################################################
	// 설정및 가져오기

	/*
	////////////////////////////////////////////////////////////////////////////
	// 모드 설정
	void CAngle::SetMode(bool bMode )
	{
		m_bMode = bMode;
	}

	////////////////////////////////////////////////////////////////////////////
	// 모드 가져오기
	bool CAngle::GetMode()
	{
		return m_bMode;
	}
	*/

	////////////////////////////////////////////////////////////////////////////
	// 도값 가져오기
	int CAngle::GetDegree()
	{
		int nDeg = (int)(m_fSecond/3600);
		if( m_bMode == true )
		{
			return (nDeg % 360);
		}
		return nDeg;
	}

	////////////////////////////////////////////////////////////////////////////
	// 분값 가져오기
	int CAngle::GetMinute()
	{
		int nMin = ((int)(m_fSecond/60)) % 60;
		return nMin;
	}

	////////////////////////////////////////////////////////////////////////////
	// 초값 가져오기
	double CAngle::GetSecond()
	{
		int nSecond = (int)m_fSecond;
		double fSecond = m_fSecond - (double)nSecond;
		nSecond = nSecond % 60;
		fSecond = (double)nSecond + fSecond;
		return fSecond;
	}

	////////////////////////////////////////////////////////////////////////////
	// 도값으로 값을 환산하여 가져오기
	double CAngle::ToDegree()
	{
		if( m_bMode == true )
		{		
			double fDeg = m_fSecond / 3600;
			double fDecimal = fDeg - (double)((int)fDeg);
			fDeg = ((double)(GetDegree())) + fDecimal;
			return fDeg;
		}
		return (m_fSecond / 3600);
	}

	////////////////////////////////////////////////////////////////////////////
	// 분값으로 값을 환산하여 가져오기
	double CAngle::ToMinute()
	{
		return (ToDegree() / 60);
	}

	////////////////////////////////////////////////////////////////////////////
	// 초값으로 값을 환산하여 가져오기
	double CAngle::ToSecond()
	{
		return (ToDegree() / 3600);
	}

	////////////////////////////////////////////////////////////////////////////
	// 라디안 값으로 가져오기
	double CAngle::ToRadian()
	{
		return (ToDegree() * _PI / 180.0);
	}

	////////////////////////////////////////////////////////////////////////////
	// 각도를 스틀링값으로 변환
	CString CAngle::ToString()
	{
		CString sTemp;
	
		sTemp.Format("%d-%d-%.3f",GetDegree(),abs(GetMinute()),abs(GetSecond()));
		return sTemp;
	}

	////////////////////////////////////////////////////////////////////////////
	// 초값으로 값을 세팅
	void CAngle::SetAngle( double fSecond )
	{
		m_fSecond = fSecond;
	}

	////////////////////////////////////////////////////////////////////////////
	// 도, 분, 초값으로 값을 세팅
	void CAngle::SetAngle( int nDeg, int nMin, double fSec )
	{
		m_fSecond = nDeg * 3600 + nMin * 60 + fSec;
	}

	////////////////////////////////////////////////////////////////////////////
	// 라디안 값으로 각도를 세팅
	void CAngle::SetAngleFromRadian( double fRadian )
	{
		SetAngle( ( fRadian * 180.0 / _PI ) * 3600 );
	}

	////////////////////////////////////////////////////////////////////////////
	// 기계로 부터 값을 받으며 nBaseValue가 360도임을 기준으로 된다. 
	void CAngle::SetAngleFromMachineInt( CString sValue, int nBaseValue )
	{
		int nValue = atoi( sValue );
		double fAngle = ((double)nValue*360.0)/(double)nBaseValue;
		double fSec = fAngle * 3600;
		SetAngle( fSec );
	}

	////////////////////////////////////////////////////////////////////////
	// 0~360도 사이의 각도로 보정
	CAngle CAngle::GetRevisionAngle()
	{
		CAngle aResult = *this;
		CAngle a360(360.0),a0(0.0);
		while( aResult < a0 ) 
		{
			aResult += a360;
		}
		while( aResult > a360 )
		{
			aResult -= a360;
		}
		return aResult;
	}
														

	// #############################################################################
	// 연산자

	////////////////////////////////////////////////////////////////////////////
	// 도 입력
	double CAngle::operator = ( double fDegree )
	{
		double fSec = fDegree * 3600;
		SetAngle( fSec );
		return fDegree;
	}

	////////////////////////////////////////////////////////////////////////////
	// 대입연산자	
	const CAngle& CAngle::operator = ( const CAngle& aSource )
	{
		_CopyFrom( aSource );
		return aSource;
	}

	////////////////////////////////////////////////////////////////////////////
	//
	CAngle CAngle::operator + ( const CAngle& aSource )
	{
		CAngle aTemp = *this;
		aTemp._Add( aSource );
		return aTemp;
	}

	////////////////////////////////////////////////////////////////////////////
	//
	CAngle CAngle::operator += ( const CAngle& aSource )
	{
		_Add( aSource );
		return *this;
	}

	////////////////////////////////////////////////////////////////////////////
	//
	CAngle CAngle::operator - ( const CAngle& aSource )
	{
		CAngle aTemp = *this;
		aTemp._Sub( aSource );
		return aTemp;
	}

	////////////////////////////////////////////////////////////////////////////
	//
	CAngle CAngle::operator -= ( const CAngle& aSource )
	{
		_Sub( aSource );
		return *this;
	}

	////////////////////////////////////////////////////////////////////////////
	// 비교연산자
	bool CAngle::operator == ( const CAngle& aSource )
	{
		if( _Compare( aSource ) == 0 ) return true;
		return false;
	}

	////////////////////////////////////////////////////////////////////////////
	//
	bool CAngle::operator != ( const CAngle& aSource )
	{
		if( _Compare( aSource ) == 0 ) return false;
		return true;
	}

	////////////////////////////////////////////////////////////////////////////
	//
	bool CAngle::operator < ( const CAngle& aSource )
	{
		if( _Compare( aSource ) < 0 ) return true;
		return false;
	}

	////////////////////////////////////////////////////////////////////////////
	//
	bool CAngle::operator > ( const CAngle& aSource )
	{
		if( _Compare( aSource ) >= 0 ) return true;
		return false;
	}

	////////////////////////////////////////////////////////////////////////////
	//
	bool CAngle::operator <= ( const CAngle& aSource )
	{
		if( _Compare( aSource ) <= 0 ) return true;
		return false;
	}

	////////////////////////////////////////////////////////////////////////////
	//
	bool CAngle::operator >= ( const CAngle& aSource )
	{
		if( _Compare( aSource ) >= 0 ) return true;
		return false;
	}



	// #############################################################################
	// 내부함수

	/////////////////////////////////////////////////////////////////////////////
	// 초기화
	void CAngle::_Init()
	{
		m_fSecond = 0;
		m_bMode = false;
	}

	////////////////////////////////////////////////////////////////////////////
	// 복사
	void CAngle::_CopyFrom( const CAngle& aSource )
	{
		this->m_fSecond = aSource.m_fSecond;
		this->m_bMode = aSource.m_bMode;
	}

	////////////////////////////////////////////////////////////////////////////
	// 비교 ( < : -1 / == : 0 / > : 1 )
	int CAngle::_Compare( const CAngle& aSource )
	{
		double fTemp = this->m_fSecond - aSource.m_fSecond;
		if( fTemp == 0 ) return 0;
		if( fTemp < 0 ) return -1;
		return 1;
	}
	////////////////////////////////////////////////////////////////////////////
	// aSource 만큼 더한다.
	void CAngle::_Add( const CAngle& aSource )
	{
		m_fSecond += aSource.m_fSecond;
	}

	////////////////////////////////////////////////////////////////////////////
	// aSource만큼 뺀다.
	void CAngle::_Sub( const CAngle& aSource )
	{
		m_fSecond -= aSource.m_fSecond;
	}

	
	void CAngle::_CalcIn360()
	{
		
	}
};