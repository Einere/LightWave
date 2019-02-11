#pragma once

#include "Shape\\DS_Polygon.h"



namespace DataType
{
	// #############################################################################
	// 필지을 나타내는 데이터 클래스이다.
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

		CString m_sUniqID;				// :고유번호
	//	CString m_sCoordList;			// :필계점
		int m_nMapNoOfMap;				// :도면번호	(도형도호)	[대장도호 / 도형도호]
		int m_nMaoNoOfReport;			// :도면번호 (대장도호)
		int m_nScale;				//	// :축척코드  
		int m_nLandObject;				// :지목코드
		CString m_sAreaSize;				// :대장면적 
	//	double m_fCalcAreaSize;			// :좌표면적	 
	//	int m_nLandMoveCause;			// :토지이동사유코드
	//	CString m_sLandMoveDate;		// :토지이동일자
	//	CString m_sRelationLandNoOfLandMoveCause;
										// :토지이동사유관련지번
										// :사업시행신고구분코드
										// :사업시행지번호
		int m_nMapType;
										// :도면구분
										// :용도지역
										// :국토계획법률
										// :다른법령
										// :토지이용규제
										// :시행령
										// :공시지가가격(m2당)
		CString m_sBasePointCode;		// :원점코드
										// :종번

	public:
		CParcel(void);
		~CParcel(void);

		bool SettingParcelFromCifString( CString sParcelData );
		bool SettingParcelFromCifFile( CStdioFile& flCifFile );

		CString GetMapKey();
		DWORD GetEntityKey();

		
		ShapeType::CDS_Polygon& GetParcelShape();
		

		// 필지 정보
		CString GetUniqID();
		CString GetLandNo(bool bUseLandObject = false);
		CString GetLandObjectFullName();
		int GetScale();
		CString GetSizeOfReport();
		double GetSizeOfCalcArea(int nUsingDigit = -1);
		CString GetBasePointCode();




	};
};
