#pragma once

#include "GPSPoint.h"

namespace DataType
{
	// #############################################################################
	// �������� ��Ÿ���� ������ Ŭ�����̴�.
	class CBasePoint
	{
	protected:
		CString m_sName;					// ���̸�
		CGPSPoint m_ptPoint;				// �� ��ġ
		CString m_sTypeCode;				// �����������ڵ�
		CString m_sAxisBasePointCode;		// �����ڵ�
		CString m_sState;					// ����
		int	m_nKey;							// Key��			// ������ : 540 / ������ : 500

//		int m_nStart
	public:
		// ======================================================
		// ������ / �Ҹ���
		CBasePoint(void);
		CBasePoint( const CBasePoint& Source );
		~CBasePoint(void);

		// ======================================================
		// ������ ������ �� ��������
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
		// ������
		virtual const CBasePoint& operator = ( const CBasePoint& Source );
		virtual bool operator == ( const CBasePoint& Source );
		virtual bool operator != ( const CBasePoint& Source );

		// ---------------------------
		// ����ȯ ����
		CString ToString(bool bSimple = false);

		// ======================================================
		// ���� �Լ�
	protected:
		void _CopyFrom( const CBasePoint& Source );
		bool _Match( const CBasePoint& Source );
		void _InitValue();
	};
};
