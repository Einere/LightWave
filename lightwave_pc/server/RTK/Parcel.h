#pragma once

#include "Shape\\DS_Polygon.h"



namespace DataType
{
	// #############################################################################
	// ������ ��Ÿ���� ������ Ŭ�����̴�.
	class CParcel
	{
		// =============================================
	protected:
		static CString ms_sLandObjectShortName[28];
		static CString ms_sLandObjectFullName[28];

	public:
		static CString GetLandObjectShortName( int nLandObjectCode );
		static CString GetLandObjectFullName( int nLandObjectCode );


		// =============================================
	protected:
		ShapeType::CDS_Polygon m_plgParcelShape;

		CString m_sUniqID;				// :������ȣ
	//	CString m_sCoordList;			// :�ʰ���
		int m_nMapNoOfMap;				// :�����ȣ	(������ȣ)	[���嵵ȣ / ������ȣ]
		int m_nMaoNoOfReport;			// :�����ȣ (���嵵ȣ)
		int m_nScale;				//	// :��ô�ڵ�  
		int m_nLandObject;				// :�����ڵ�
		CString m_sAreaSize;				// :������� 
	//	double m_fCalcAreaSize;			// :��ǥ����	 
	//	int m_nLandMoveCause;			// :�����̵������ڵ�
	//	CString m_sLandMoveDate;		// :�����̵�����
	//	CString m_sRelationLandNoOfLandMoveCause;
										// :�����̵�������������
										// :�������Ű����ڵ�
										// :�����������ȣ
		int m_nMapType;
										// :���鱸��
										// :�뵵����
										// :�����ȹ����
										// :�ٸ�����
										// :�����̿����
										// :�����
										// :������������(m2��)
		CString m_sBasePointCode;		// :�����ڵ�
										// :����

	public:
		CParcel(void);
		~CParcel(void);

		bool SettingParcelFromCifString( CString sParcelData );
		bool SettingParcelFromCifFile( CStdioFile& flCifFile );

		CString GetMapKey();
		DWORD GetEntityKey();

		
		ShapeType::CDS_Polygon& GetParcelShape();
		

		// ���� ����
		CString GetUniqID();
		CString GetLandNo(bool bUseLandObject = false);
		CString GetLandObjectFullName();
		int GetScale();
		CString GetSizeOfReport();
		double GetSizeOfCalcArea(int nUsingDigit = -1);
		CString GetBasePointCode();




	};
};
