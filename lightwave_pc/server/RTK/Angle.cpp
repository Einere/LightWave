#include "StdAfx.h"
#include "Angle.h"
#include <valarray>




namespace DataType
{
	// #############################################################################
	// ������

	////////////////////////////////////////////////////////////////////////////
	// 0���� ������ ����
	CAngle::CAngle(void)
	{
		_Init();
	}

	////////////////////////////////////////////////////////////////////////////
	// �ʸ� �Է¹޾Ƽ� ������ ����
	CAngle::CAngle(double fDegree)
	{
		_Init();
		double fSec = fDegree * 3600;
		SetAngle( fSec );
	}

	////////////////////////////////////////////////////////////////////////////
	// �����ʸ� �Է¹޾Ƽ� ������ ����		
	CAngle::CAngle(int nDeg,int nMin,double fSec)
	{
		_Init();
		SetAngle( nDeg, nMin, fSec );
	}

	////////////////////////////////////////////////////////////////////////////
	// ���������
	CAngle::CAngle(const CAngle& aSource )
	{
		_Init();
		_CopyFrom( aSource );
	}

	////////////////////////////////////////////////////////////////////////////
	// �Ҹ���
	CAngle::~CAngle(void)
	{
	
	}



	// #############################################################################
	// ������ ��������

	/*
	////////////////////////////////////////////////////////////////////////////
	// ��� ����
	void CAngle::SetMode(bool bMode )
	{
		m_bMode = bMode;
	}

	////////////////////////////////////////////////////////////////////////////
	// ��� ��������
	bool CAngle::GetMode()
	{
		return m_bMode;
	}
	*/

	////////////////////////////////////////////////////////////////////////////
	// ���� ��������
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
	// �а� ��������
	int CAngle::GetMinute()
	{
		int nMin = ((int)(m_fSecond/60)) % 60;
		return nMin;
	}

	////////////////////////////////////////////////////////////////////////////
	// �ʰ� ��������
	double CAngle::GetSecond()
	{
		int nSecond = (int)m_fSecond;
		double fSecond = m_fSecond - (double)nSecond;
		nSecond = nSecond % 60;
		fSecond = (double)nSecond + fSecond;
		return fSecond;
	}

	////////////////////////////////////////////////////////////////////////////
	// �������� ���� ȯ���Ͽ� ��������
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
	// �а����� ���� ȯ���Ͽ� ��������
	double CAngle::ToMinute()
	{
		return (ToDegree() / 60);
	}

	////////////////////////////////////////////////////////////////////////////
	// �ʰ����� ���� ȯ���Ͽ� ��������
	double CAngle::ToSecond()
	{
		return (ToDegree() / 3600);
	}

	////////////////////////////////////////////////////////////////////////////
	// ���� ������ ��������
	double CAngle::ToRadian()
	{
		return (ToDegree() * _PI / 180.0);
	}

	////////////////////////////////////////////////////////////////////////////
	// ������ ��Ʋ�������� ��ȯ
	CString CAngle::ToString()
	{
		CString sTemp;
	
		sTemp.Format("%d-%d-%.3f",GetDegree(),abs(GetMinute()),abs(GetSecond()));
		return sTemp;
	}

	////////////////////////////////////////////////////////////////////////////
	// �ʰ����� ���� ����
	void CAngle::SetAngle( double fSecond )
	{
		m_fSecond = fSecond;
	}

	////////////////////////////////////////////////////////////////////////////
	// ��, ��, �ʰ����� ���� ����
	void CAngle::SetAngle( int nDeg, int nMin, double fSec )
	{
		m_fSecond = nDeg * 3600 + nMin * 60 + fSec;
	}

	////////////////////////////////////////////////////////////////////////////
	// ���� ������ ������ ����
	void CAngle::SetAngleFromRadian( double fRadian )
	{
		SetAngle( ( fRadian * 180.0 / _PI ) * 3600 );
	}

	////////////////////////////////////////////////////////////////////////////
	// ���� ���� ���� ������ nBaseValue�� 360������ �������� �ȴ�. 
	void CAngle::SetAngleFromMachineInt( CString sValue, int nBaseValue )
	{
		int nValue = atoi( sValue );
		double fAngle = ((double)nValue*360.0)/(double)nBaseValue;
		double fSec = fAngle * 3600;
		SetAngle( fSec );
	}

	////////////////////////////////////////////////////////////////////////
	// 0~360�� ������ ������ ����
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
	// ������

	////////////////////////////////////////////////////////////////////////////
	// �� �Է�
	double CAngle::operator = ( double fDegree )
	{
		double fSec = fDegree * 3600;
		SetAngle( fSec );
		return fDegree;
	}

	////////////////////////////////////////////////////////////////////////////
	// ���Կ�����	
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
	// �񱳿�����
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
	// �����Լ�

	/////////////////////////////////////////////////////////////////////////////
	// �ʱ�ȭ
	void CAngle::_Init()
	{
		m_fSecond = 0;
		m_bMode = false;
	}

	////////////////////////////////////////////////////////////////////////////
	// ����
	void CAngle::_CopyFrom( const CAngle& aSource )
	{
		this->m_fSecond = aSource.m_fSecond;
		this->m_bMode = aSource.m_bMode;
	}

	////////////////////////////////////////////////////////////////////////////
	// �� ( < : -1 / == : 0 / > : 1 )
	int CAngle::_Compare( const CAngle& aSource )
	{
		double fTemp = this->m_fSecond - aSource.m_fSecond;
		if( fTemp == 0 ) return 0;
		if( fTemp < 0 ) return -1;
		return 1;
	}
	////////////////////////////////////////////////////////////////////////////
	// aSource ��ŭ ���Ѵ�.
	void CAngle::_Add( const CAngle& aSource )
	{
		m_fSecond += aSource.m_fSecond;
	}

	////////////////////////////////////////////////////////////////////////////
	// aSource��ŭ ����.
	void CAngle::_Sub( const CAngle& aSource )
	{
		m_fSecond -= aSource.m_fSecond;
	}

	
	void CAngle::_CalcIn360()
	{
		
	}
};