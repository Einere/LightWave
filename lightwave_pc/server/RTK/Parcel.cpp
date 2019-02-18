#include "StdAfx.h"
#include "Parcel.h"
#include "GlobalUtil\\StringUtil.h"

using namespace GlobalUtil;
namespace DataType
{
	CString CParcel::ms_sLandObjectShortName[] = {"전","답","과","목","임","광","염","대","장","학","차","주","창","도","철","제","천","구","유","양","수","공","체","원","종","사","묘","잡"};
	CString CParcel::ms_sLandObjectFullName[] = {"전","답","과수원","목장용지","임야","광천지","염전","대","공장용지","학교용지","주차장","주유소용지","창고용지","도로","철도용지","제방","하천","구거","유지","양어장","수도용지","공원","체육용지","유원지","종교용지","사적지","묘지","잡종지"};

	CString CParcel::GetLandObjectShortName( int nLandObjectCode )
	{
		if( nLandObjectCode < 1 || nLandObjectCode > 28 ) return "기타";
		return ms_sLandObjectShortName[nLandObjectCode-1];
	}

	CString CParcel::GetLandObjectFullName( int nLandObjectCode )
	{
		if( nLandObjectCode < 1 || nLandObjectCode > 28 ) return "기타";
		return ms_sLandObjectFullName[nLandObjectCode-1];
	}

	CParcel::CParcel(void)
	{
		m_sUniqID = "";				// :고유번호
	//	CString m_sCoordList;			// :필계점
		m_nMapNoOfMap = 0;				// :도면번호	(도형도호)	[대장도호 / 도형도호]
		m_nMaoNoOfReport = 0;			// :도면번호 (대장도호)
		m_nScale = 0;				//	// :축척코드  
		m_nLandObject = 0;			// :지목코드
		m_sAreaSize = "0";				// :대장면적 
	//	double m_fCalcAreaSize;			// :좌표면적	 
	//	int m_nLandMoveCause;			// :토지이동사유코드
	//	CString m_sLandMoveDate;		// :토지이동일자
	//	CString m_sRelationLandNoOfLandMoveCause;
										// :토지이동사유관련지번
										// :사업시행신고구분코드
										// :사업시행지번호
		m_nMapType = 0;
										// :도면구분
										// :용도지역
										// :국토계획법률
										// :다른법령
										// :토지이용규제
										// :시행령
										// :공시지가가격(m2당)
										// :원점코드
										// :종번
	}


	CParcel::~CParcel(void)
	{
	}

	bool CParcel::SettingParcelFromCifString( CString sParcelData )
	{
		CArray<CString> lsStringList;			
		int nReadCount = CStringUtil::CuttingStringToList(sParcelData,"\n",lsStringList);
		
		int nListIndex = 0;
		CString sNowTag;
		while( nListIndex < nReadCount )
		{
			sNowTag = lsStringList[nListIndex];
			sNowTag = sNowTag.Trim();
			if( sNowTag[0] == '<' )
			{
				// 긴급상황 필지정보 안에서 꺽쇠가 나와서는 안된다.
				break;
			}
			if( sNowTag[0] != ':' )
			{
				nListIndex++;
				continue;
			}
			/*
			CString m_sUniqID;				// :고유번호
	//	CString m_sCoordList;			// :필계점
		int m_nMapNoOfMap;				// :도면번호	(도형도호)	[대장도호 / 도형도호]
		int m_nMaoNoOfReport;			// :도면번호 (대장도호)
		int m_nScale;				//	// :축척코드  
		CString m_sLandObject;			// :지목코드
		double m_fAreaSize;				// :대장면적 
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
										// :원점코드
										// :종번
		*/
			if( sNowTag == ":고유번호" )
			{
				nListIndex++;
				CString sValueBuf = lsStringList[nListIndex];
				m_sUniqID = sValueBuf;
				if( m_sUniqID == "2871033024112850000" )
				{
					int dafdfa = 121231;
				}
				nListIndex ++;
				continue;
			}
			if( sNowTag == ":필계점" )
			{
				nListIndex++;
				if( m_plgParcelShape.InitWithCifStringArray( lsStringList, nListIndex ) == false )
				{
					// 필계점 가져오기 실패
					return false;
				}
				continue;
			}
			if( sNowTag == ":도면번호" )
			{	// [대장도호 / 도형도호]
				nListIndex++;
				CString sValueBuf = lsStringList[nListIndex];

				int nSearchIndex = sValueBuf.Find("/");
				CString sMapNoOfReport,sMapNoOfMap;
				if( nSearchIndex >= 0 )
				{
					sMapNoOfReport =  sValueBuf.Left( nSearchIndex );
					sMapNoOfMap = sValueBuf.Right( sValueBuf.GetLength() - nSearchIndex - 1 );
				}
				else
				{
					sMapNoOfReport =  sValueBuf;
					sMapNoOfMap = sValueBuf;
				}

				if( sMapNoOfMap == "" ) m_nMapNoOfMap = 0;
				else m_nMapNoOfMap = atoi( sMapNoOfMap );

				if( sMapNoOfReport == "" ) m_nMaoNoOfReport = 0;
				else m_nMaoNoOfReport = atoi( sMapNoOfReport );
				
				nListIndex ++;
				continue;
			}
			if( sNowTag == ":축척코드" )
			{
				nListIndex++;
				CString sValueBuf = lsStringList[nListIndex];

				if( sValueBuf == "" ) m_nScale = 0;
				else m_nScale = atoi( sValueBuf );

				nListIndex ++;
				continue;

			}
			if( sNowTag == ":지목코드" )
			{
				nListIndex++;
				CString sValueBuf = lsStringList[nListIndex];

				m_nLandObject = atoi(sValueBuf);
				
				nListIndex ++;
				continue;

			}
			if( sNowTag == ":대장면적" )
			{
				nListIndex++;
				CString sValueBuf = lsStringList[nListIndex];

				m_sAreaSize = sValueBuf;
				
				nListIndex ++;
				continue;

			}
			if( sNowTag == ":좌표면적" )
			{
				nListIndex++;
				CString sValueBuf = lsStringList[nListIndex];

				
				nListIndex ++;
				continue;

			}
			if( sNowTag == ":토지이동사유코드" )
			{
				nListIndex++;
				CString sValueBuf = lsStringList[nListIndex];

				
				nListIndex ++;
				continue;

			}
			if( sNowTag == ":토지이동일자" )
			{
				nListIndex++;
				CString sValueBuf = lsStringList[nListIndex];

				
				nListIndex ++;
				continue;

			}
			if( sNowTag == ":토지이동사유관련지번" )
			{
				nListIndex++;
				CString sValueBuf = lsStringList[nListIndex];

				
				nListIndex ++;
				continue;

			}
			if( sNowTag == ":사업시행신고구분코드" )
			{
				nListIndex++;
				CString sValueBuf = lsStringList[nListIndex];

				
				nListIndex ++;
				continue;

			}
			if( sNowTag == ":사업시행지번호" )
			{
				nListIndex++;
				CString sValueBuf = lsStringList[nListIndex];

				
				nListIndex ++;
				continue;

			}
			if( sNowTag == ":도면구분" )
			{
				nListIndex++;
				CString sValueBuf = lsStringList[nListIndex];

				if( sValueBuf == "" ) m_nMapType = 0;
				else m_nMapType = atoi( sValueBuf );
				
				nListIndex ++;
				continue;

			}
			if( sNowTag == ":용도지역" )
			{
				nListIndex++;
				CString sValueBuf = lsStringList[nListIndex];

				
				nListIndex ++;
				continue;

			}
			if( sNowTag == ":국토계획법률" )
			{
				nListIndex++;
				CString sValueBuf = lsStringList[nListIndex];

				
				nListIndex ++;
				continue;

			}
			if( sNowTag == ":다른법령" )
			{
				nListIndex++;
				CString sValueBuf = lsStringList[nListIndex];

				
				nListIndex ++;
				continue;

			}
			if( sNowTag == ":토지이용규제" )
			{
				nListIndex++;
				CString sValueBuf = lsStringList[nListIndex];

				
				nListIndex ++;
				continue;

			}
			if( sNowTag == ":시행령" )
			{
				nListIndex++;
				CString sValueBuf = lsStringList[nListIndex];

				
				nListIndex ++;
				continue;

			}
			if( sNowTag == ":공시지가가격(m2당)" )
			{
				nListIndex++;
				CString sValueBuf = lsStringList[nListIndex];

				
				nListIndex ++;
				continue;

			}
			if( sNowTag == ":원점코드" )
			{
				nListIndex++;
				CString sValueBuf = lsStringList[nListIndex];

				
				nListIndex ++;
				continue;

			}
			if( sNowTag == ":종번" )
			{
				nListIndex++;
				CString sValueBuf = lsStringList[nListIndex];

				
				nListIndex ++;
				continue;
			}
			// 그외
			nListIndex ++;
		}

		return true;
	}

	bool CParcel::SettingParcelFromCifFile( CStdioFile& flCifFile )
	{
		CString sTagBuf;
		CString sReadBuf;
		CString sDataBuf;
		while( true )
		{
			long nPos = flCifFile.GetPosition();
			flCifFile.ReadString( sReadBuf );
			sReadBuf = sReadBuf.Trim();
			if( sReadBuf[0] == '<' )
			{
				flCifFile.Seek( nPos, CFile::begin );
				if( m_sUniqID != "" ) return true;
				else return false;
			}
			if( sReadBuf[0] != ':' )
			{
				continue;
			}
			if( sReadBuf == ":고유번호" )
			{
				flCifFile.ReadString( sReadBuf );
				sReadBuf = sReadBuf.Trim();
				m_sUniqID = sReadBuf;
				continue;
			}
			if( sReadBuf == ":필계점" )
			{
				if( m_plgParcelShape.InitWithCifFile( flCifFile ) == false )
				{
					// 필계점 가져오기 실패
					return false;
				}
				continue;
			}
			if( sReadBuf == ":도면번호" )
			{	// [대장도호 / 도형도호]
				flCifFile.ReadString( sReadBuf );
				sReadBuf = sReadBuf.Trim();

				int nSearchIndex = sReadBuf.Find("/");
				CString sMapNoOfReport,sMapNoOfMap;
				if( nSearchIndex >= 0 )
				{
					sMapNoOfReport =  sReadBuf.Left( nSearchIndex );
					sMapNoOfMap = sReadBuf.Right( sReadBuf.GetLength() - nSearchIndex - 1 );
				}
				else
				{
					sMapNoOfReport =  sReadBuf;
					sMapNoOfMap = sReadBuf;
				}

				if( sMapNoOfMap == "" ) m_nMapNoOfMap = 0;
				else m_nMapNoOfMap = atoi( sMapNoOfMap );

				if( sMapNoOfReport == "" ) m_nMaoNoOfReport = 0;
				else m_nMaoNoOfReport = atoi( sMapNoOfReport );
				
				continue;
			}
			if( sReadBuf == ":대장면적" )
			{
				flCifFile.ReadString( sReadBuf );
				sReadBuf = sReadBuf.Trim();

				m_sAreaSize = sReadBuf;

				continue;

			}
			if( sReadBuf == ":축척코드" )
			{
				flCifFile.ReadString( sReadBuf );
				sReadBuf = sReadBuf.Trim();
				int nSlashIndex = sReadBuf.Find("/");
				if( nSlashIndex >= 0 ) sReadBuf = sReadBuf.Right( sReadBuf.GetLength() - nSlashIndex - 1 );
				if( sReadBuf == "" ) m_nScale = 0;
				else m_nScale = atoi( sReadBuf );

				continue;

			}
			if( sReadBuf == ":지목코드" )
			{
				flCifFile.ReadString( sReadBuf );
				sReadBuf = sReadBuf.Trim();
				m_nLandObject = atoi(sReadBuf);
				
				continue;

			}
			if( sReadBuf == ":도면구분" )
			{
				flCifFile.ReadString( sReadBuf );
				sReadBuf = sReadBuf.Trim();
				if( sReadBuf == "" ) m_nMapType = 0;
				else m_nMapType = atoi( sReadBuf );

				continue;

			}
			if( sReadBuf == ":종번" )
			{
				flCifFile.ReadString( sReadBuf );
				sReadBuf = sReadBuf.Trim();

				continue;
			}
			if( sReadBuf == ":원점코드" )
			{
				flCifFile.ReadString( sReadBuf );
				sReadBuf = sReadBuf.Trim();
				m_sBasePointCode = sReadBuf;
				continue;
			}

		}

	}

	CString CParcel::GetMapKey()
	{
		CString sKey,sDoho;
		sDoho.Format("%d",1000 + m_nMapNoOfMap );
		sKey.Format("%s_%s",m_sUniqID,sDoho.Right(3));
		return sKey;
	}

	DWORD CParcel::GetEntityKey()
	{
		long nKey = m_nScale *  1000 + m_nMapNoOfMap;
		return nKey;
	}

	CString CParcel::GetUniqID()
	{
		return m_sUniqID;
	}

	ShapeType::CDS_Polygon& CParcel::GetParcelShape()
	{
		return m_plgParcelShape;
	}

	CString CParcel::GetLandNo(bool bUseLandObject)
	{
		CString sTemp = m_sUniqID.Right( 8 );
		CString sLeft = sTemp.Left(4);
		CString sRight = sTemp.Right( 4 );
		int nLeft = atoi( sLeft );
		int nRight = atoi( sRight );
		CString sLandNo;
		if( nRight > 0 )
		{
			sLandNo.Format("%d-%d",nLeft,nRight );
		}
		else
		{
			sLandNo.Format("%d",nLeft);
		}
		if( bUseLandObject == true )
		{
			sLandNo += " ";
			sLandNo += GetLandObjectShortName(m_nLandObject);
		}
		return sLandNo;
	}

	CString CParcel::GetLandObjectFullName()
	{
		return GetLandObjectFullName(m_nLandObject);
	}

	int CParcel::GetScale()
	{
		if( m_nScale < 100 ) return m_nScale * 100;
		return m_nScale;
	}

	CString CParcel::GetSizeOfReport()
	{
		return m_sAreaSize;
	}

	double CParcel::GetSizeOfCalcArea(int nUsingDigit)
	{
		return m_plgParcelShape.GetAreaSize(nUsingDigit);
	}

	CString CParcel::GetBasePointCode()
	{
		return m_sBasePointCode;
	}
};