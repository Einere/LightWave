#include "StdAfx.h"
#include "Parcel.h"
#include "GlobalUtil\\StringUtil.h"

using namespace GlobalUtil;
namespace DataType
{
	CString CParcel::ms_sLandObjectShortName[] = {"��","��","��","��","��","��","��","��","��","��","��","��","â","��","ö","��","õ","��","��","��","��","��","ü","��","��","��","��","��"};
	CString CParcel::ms_sLandObjectFullName[] = {"��","��","������","�������","�Ӿ�","��õ��","����","��","�������","�б�����","������","�����ҿ���","â�����","����","ö������","����","��õ","����","����","�����","��������","����","ü������","������","��������","������","����","������"};

	CString CParcel::GetLandObjectShortName( int nLandObjectCode )
	{
		if( nLandObjectCode < 1 || nLandObjectCode > 28 ) return "��Ÿ";
		return ms_sLandObjectShortName[nLandObjectCode-1];
	}

	CString CParcel::GetLandObjectFullName( int nLandObjectCode )
	{
		if( nLandObjectCode < 1 || nLandObjectCode > 28 ) return "��Ÿ";
		return ms_sLandObjectFullName[nLandObjectCode-1];
	}

	CParcel::CParcel(void)
	{
		m_sUniqID = "";				// :������ȣ
	//	CString m_sCoordList;			// :�ʰ���
		m_nMapNoOfMap = 0;				// :�����ȣ	(������ȣ)	[���嵵ȣ / ������ȣ]
		m_nMaoNoOfReport = 0;			// :�����ȣ (���嵵ȣ)
		m_nScale = 0;				//	// :��ô�ڵ�  
		m_nLandObject = 0;			// :�����ڵ�
		m_sAreaSize = "0";				// :������� 
	//	double m_fCalcAreaSize;			// :��ǥ����	 
	//	int m_nLandMoveCause;			// :�����̵������ڵ�
	//	CString m_sLandMoveDate;		// :�����̵�����
	//	CString m_sRelationLandNoOfLandMoveCause;
										// :�����̵�������������
										// :�������Ű����ڵ�
										// :�����������ȣ
		m_nMapType = 0;
										// :���鱸��
										// :�뵵����
										// :�����ȹ����
										// :�ٸ�����
										// :�����̿����
										// :�����
										// :������������(m2��)
										// :�����ڵ�
										// :����
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
				// ��޻�Ȳ �������� �ȿ��� ���谡 ���ͼ��� �ȵȴ�.
				break;
			}
			if( sNowTag[0] != ':' )
			{
				nListIndex++;
				continue;
			}
			/*
			CString m_sUniqID;				// :������ȣ
	//	CString m_sCoordList;			// :�ʰ���
		int m_nMapNoOfMap;				// :�����ȣ	(������ȣ)	[���嵵ȣ / ������ȣ]
		int m_nMaoNoOfReport;			// :�����ȣ (���嵵ȣ)
		int m_nScale;				//	// :��ô�ڵ�  
		CString m_sLandObject;			// :�����ڵ�
		double m_fAreaSize;				// :������� 
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
										// :�����ڵ�
										// :����
		*/
			if( sNowTag == ":������ȣ" )
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
			if( sNowTag == ":�ʰ���" )
			{
				nListIndex++;
				if( m_plgParcelShape.InitWithCifStringArray( lsStringList, nListIndex ) == false )
				{
					// �ʰ��� �������� ����
					return false;
				}
				continue;
			}
			if( sNowTag == ":�����ȣ" )
			{	// [���嵵ȣ / ������ȣ]
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
			if( sNowTag == ":��ô�ڵ�" )
			{
				nListIndex++;
				CString sValueBuf = lsStringList[nListIndex];

				if( sValueBuf == "" ) m_nScale = 0;
				else m_nScale = atoi( sValueBuf );

				nListIndex ++;
				continue;

			}
			if( sNowTag == ":�����ڵ�" )
			{
				nListIndex++;
				CString sValueBuf = lsStringList[nListIndex];

				m_nLandObject = atoi(sValueBuf);
				
				nListIndex ++;
				continue;

			}
			if( sNowTag == ":�������" )
			{
				nListIndex++;
				CString sValueBuf = lsStringList[nListIndex];

				m_sAreaSize = sValueBuf;
				
				nListIndex ++;
				continue;

			}
			if( sNowTag == ":��ǥ����" )
			{
				nListIndex++;
				CString sValueBuf = lsStringList[nListIndex];

				
				nListIndex ++;
				continue;

			}
			if( sNowTag == ":�����̵������ڵ�" )
			{
				nListIndex++;
				CString sValueBuf = lsStringList[nListIndex];

				
				nListIndex ++;
				continue;

			}
			if( sNowTag == ":�����̵�����" )
			{
				nListIndex++;
				CString sValueBuf = lsStringList[nListIndex];

				
				nListIndex ++;
				continue;

			}
			if( sNowTag == ":�����̵�������������" )
			{
				nListIndex++;
				CString sValueBuf = lsStringList[nListIndex];

				
				nListIndex ++;
				continue;

			}
			if( sNowTag == ":�������Ű����ڵ�" )
			{
				nListIndex++;
				CString sValueBuf = lsStringList[nListIndex];

				
				nListIndex ++;
				continue;

			}
			if( sNowTag == ":�����������ȣ" )
			{
				nListIndex++;
				CString sValueBuf = lsStringList[nListIndex];

				
				nListIndex ++;
				continue;

			}
			if( sNowTag == ":���鱸��" )
			{
				nListIndex++;
				CString sValueBuf = lsStringList[nListIndex];

				if( sValueBuf == "" ) m_nMapType = 0;
				else m_nMapType = atoi( sValueBuf );
				
				nListIndex ++;
				continue;

			}
			if( sNowTag == ":�뵵����" )
			{
				nListIndex++;
				CString sValueBuf = lsStringList[nListIndex];

				
				nListIndex ++;
				continue;

			}
			if( sNowTag == ":�����ȹ����" )
			{
				nListIndex++;
				CString sValueBuf = lsStringList[nListIndex];

				
				nListIndex ++;
				continue;

			}
			if( sNowTag == ":�ٸ�����" )
			{
				nListIndex++;
				CString sValueBuf = lsStringList[nListIndex];

				
				nListIndex ++;
				continue;

			}
			if( sNowTag == ":�����̿����" )
			{
				nListIndex++;
				CString sValueBuf = lsStringList[nListIndex];

				
				nListIndex ++;
				continue;

			}
			if( sNowTag == ":�����" )
			{
				nListIndex++;
				CString sValueBuf = lsStringList[nListIndex];

				
				nListIndex ++;
				continue;

			}
			if( sNowTag == ":������������(m2��)" )
			{
				nListIndex++;
				CString sValueBuf = lsStringList[nListIndex];

				
				nListIndex ++;
				continue;

			}
			if( sNowTag == ":�����ڵ�" )
			{
				nListIndex++;
				CString sValueBuf = lsStringList[nListIndex];

				
				nListIndex ++;
				continue;

			}
			if( sNowTag == ":����" )
			{
				nListIndex++;
				CString sValueBuf = lsStringList[nListIndex];

				
				nListIndex ++;
				continue;
			}
			// �׿�
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
			if( sReadBuf == ":������ȣ" )
			{
				flCifFile.ReadString( sReadBuf );
				sReadBuf = sReadBuf.Trim();
				m_sUniqID = sReadBuf;
				continue;
			}
			if( sReadBuf == ":�ʰ���" )
			{
				if( m_plgParcelShape.InitWithCifFile( flCifFile ) == false )
				{
					// �ʰ��� �������� ����
					return false;
				}
				continue;
			}
			if( sReadBuf == ":�����ȣ" )
			{	// [���嵵ȣ / ������ȣ]
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
			if( sReadBuf == ":�������" )
			{
				flCifFile.ReadString( sReadBuf );
				sReadBuf = sReadBuf.Trim();

				m_sAreaSize = sReadBuf;

				continue;

			}
			if( sReadBuf == ":��ô�ڵ�" )
			{
				flCifFile.ReadString( sReadBuf );
				sReadBuf = sReadBuf.Trim();
				int nSlashIndex = sReadBuf.Find("/");
				if( nSlashIndex >= 0 ) sReadBuf = sReadBuf.Right( sReadBuf.GetLength() - nSlashIndex - 1 );
				if( sReadBuf == "" ) m_nScale = 0;
				else m_nScale = atoi( sReadBuf );

				continue;

			}
			if( sReadBuf == ":�����ڵ�" )
			{
				flCifFile.ReadString( sReadBuf );
				sReadBuf = sReadBuf.Trim();
				m_nLandObject = atoi(sReadBuf);
				
				continue;

			}
			if( sReadBuf == ":���鱸��" )
			{
				flCifFile.ReadString( sReadBuf );
				sReadBuf = sReadBuf.Trim();
				if( sReadBuf == "" ) m_nMapType = 0;
				else m_nMapType = atoi( sReadBuf );

				continue;

			}
			if( sReadBuf == ":����" )
			{
				flCifFile.ReadString( sReadBuf );
				sReadBuf = sReadBuf.Trim();

				continue;
			}
			if( sReadBuf == ":�����ڵ�" )
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