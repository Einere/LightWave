#pragma once

#include "GPSPoint.h"

namespace DataType
{
	// #############################################################################
	// 기준점을 나타내는 데이터 클래스이다.
	class CBasePoint
	{
	protected:
		CString m_sName;					// 점이름
		CGPSPoint m_ptPoint;				// 점 위치
		CString m_sTypeCode;				// 기준점종류코드
		CString m_sAxisBasePointCode;		// 원점코드
		CString m_sState;					// 상태
		int	m_nKey;							// Key값			// 도근점 : 540 / 측량점 : 500

//		int m_nStart
	public:
		// ======================================================
		// 생성자 / 소멸자
		CBasePoint(void);
		CBasePoint( const CBasePoint& Source );
		~CBasePoint(void);

		// ======================================================
		// 기준점 설정및 값 가져오기
		bool SettingBastPointFromCifString( CString sPointData );
		bool SettingBasePointFromCifFile( CStdioFile& flCifFile );

		void SetPosition( CGPSPoint ptPosition );
		void SetPointName( CString sName );
		void SetKey( int nKey );

		CString GetPointName();
		CString GetUniqKey();		// PointName;
		DWORD GetEntityKey();
		CGPSPoint GetPosition();
		int GetKey();
		
		// ------------------------------------
		CTime GetSurveyTime();

		// ======================================================
		// 연산자
		virtual const CBasePoint& operator = ( const CBasePoint& Source );
		virtual bool operator == ( const CBasePoint& Source );
		virtual bool operator != ( const CBasePoint& Source );

		// ---------------------------
		// 형변환 관련
		CString ToString(bool bSimple = false);

		// ======================================================
		// 내부 함수
	protected:
		void _CopyFrom( const CBasePoint& Source );
		bool _Match( const CBasePoint& Source );
		void _InitValue();
	};
};
