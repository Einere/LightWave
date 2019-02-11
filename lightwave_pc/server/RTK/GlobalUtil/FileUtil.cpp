#include "stdafx.h"
#include <stdio.h>
#include "FileUtil.h"

namespace GlobalUtil
{
	// ====================================================
	/*
	CFileUtil* CFileUtil::m_pThis = NULL;
	

	CFileUtil* CFileUtil::GetInstance()
	{
		if( m_pThis == NULL )
		{
			m_pThis = new CFileUtil;
		}
		return m_pThis;
	}

	void CFileUtil::ReleaseInstance()
	{
		if( m_pThis != NULL )
		{
			delete m_pThis;
			m_pThis = NULL;
		}
	}
	*/

	// ====================================================

//	FILE* m_pFile;
//	CString sFileName;
//	CString sFileOption;

	CFileUtil::CFileUtil()
	{
		m_pFile = NULL;
		m_sFileName = "";
		m_sFileOption = "";
	}

	CFileUtil::~CFileUtil()
	{
		if( m_pFile != NULL )
		{
			FileClose();
		}
	}


	bool CFileUtil::SetFilePointer( FILE *pFile , bool bClose )
	{
		if( bClose == true ) FileClose();
		m_pFile = pFile;
		return true;
	}

	//////////////////////////////////////////////////////////
	// ���� ������ ���������� �̸��� �����Ҽ� ����.
	bool CFileUtil::SetFileName( CString sFileName )
	{
		if( m_pFile != NULL ) return false;
		m_sFileName = sFileName;
		return true;
	}

	//////////////////////////////////////////////////////////
	// ���� �ɼ� ���� ( ���������� ���������� �����Ҽ� ���� )
	bool CFileUtil::SetFileOpenMode( CString sOption )
	{
		if( m_pFile != NULL ) return false;
		m_sFileOption = sOption;
		return true;
	}

	//////////////////////////////////////////////////////////
	// ���� ����
	bool CFileUtil::FileOpen(CString sFileName, CString sFileOption)
	{
		if( m_pFile != NULL ) return false;
		m_sFileName = sFileName;
		m_sFileOption = sFileOption;
		if( m_sFileName == "" || m_sFileOption == "" ) return false;
		m_pFile = fopen( m_sFileName, m_sFileOption );
		if( m_pFile == NULL ) return false;
		return true;
	}

	//////////////////////////////////////////////////////////
	// ���� ����
	bool CFileUtil::FileOpen()
	{
		if( m_sFileName == "" || m_sFileOption == "" ) return false;
		m_pFile = fopen( m_sFileName, m_sFileOption );
		if( m_pFile == NULL ) return false;
		return true;
	}

	//////////////////////////////////////////////////////////
	// ���� �ݱ�
	bool CFileUtil::FileClose()
	{
		if( m_pFile == NULL ) return false;
		fclose( m_pFile );
		m_pFile = NULL;
		return true;
	}

	// ������ �������� ����ϴ�.
	bool CFileUtil::IsNowEndPos()
	{
		bool bfEnd = (bool)(feof( m_pFile ));
		bool bpEnd = false;
		long nNowPos = GetPos();
		long nEndPos = GetEndPos();
		if( nNowPos >= nEndPos ) bpEnd = true;
		if( bfEnd == true ) return true;
		if( bpEnd == true ) return true;
		return false;
	}


	// ====================================
	//////////////////////////////////////////////////////////
	// ���� �����ִ��� Ȯ���մϴ�.
	bool CFileUtil::IsOpen()
	{
		if( m_pFile == NULL ) return false;
		return true;
	}


	// ====================================
	//////////////////////////////////////////////////////////
	// �Ѱ��� �����ڿ��� �յڰ� ���еǾ��ִ� ���� �����´�.
	bool CFileUtil::ReadBlock( CString sBlock, CString& sReadBuf )				
	{
		return ReadBlock(sBlock, sBlock, sReadBuf );
	}

	//////////////////////////////////////////////////////////
	// �յڷ� �ٸ� �����ڿ��� ���еǾ��մ� ���� �����´�.
	bool CFileUtil::ReadBlock( CString sSBlock, CString sEBlock, CString& sReadBuf )	
	{
		if( IsOpen() == false ) return false;
		
		CString sTemp;
		CString sSavingTemp;
	//	char sBuf[3000];
		CString sBuf;
		long nStartPosition = GetPos();

		bool bOpenBlock = false;
		while( IsNowEndPos() == false )
		{
			if( ReadLine( sBuf ) == false )
			{
				break;
			}
	//		fscanf(fp,"%s\n",sBuf);
			if( bOpenBlock == false )	// ���� BlockStartString�� ã����
			{
				if( sSBlock == sBuf )
				{
					bOpenBlock = true;
				}
			}
			else						// BlockStartString�� ã���� sBlockEndString�� ã����
			{
				if( sEBlock == sBuf )
				{
					sReadBuf = sSavingTemp;	// �˻��� �����ٸ� ������� ã�� ������ �Ѱ��ְ� 
					return true;				// true ����
				}
				else
				{
					if( sSavingTemp.GetLength() > 0 ) sSavingTemp = sSavingTemp + "\n";
					sSavingTemp = sSavingTemp + sBuf;
				}
			}
		}
		// ã�� �����Ͽ���.( Ŀ���� �Լ������Ҷ��� ��ġ�� �ǵ�����. )
		SetPos( nStartPosition );
		return false;
	}

	//////////////////////////////////////////////////////////
	// �� ������ �о�´�.
	long CFileUtil::ReadLine( CString& sReadBuf )
	{
		return _ReadToChar('\n',sReadBuf);
		// --------------
		/*
		if( IsOpen() == false ) return false;
	
		long nStartPos = GetPos();

		char sTemp[3000];
		
		int nNowCount = 0;
		while( IsNowEndPos() == false )
		{
			long nReadSize = fread(sTemp,sizeof(char),1,m_pFile);
			if( nReadSize <= 0 ) 
			{
				long nsisisis = -1;
			}
			long fPosTemp = GetPos();
			if( sTemp[0] == '\n' && nNowCount > 0 )
			{
				long nEndPos = GetPos();
				long nSize = nEndPos - nStartPos - 1;
				if( nSize <= 0 )
				{	
	//				fseek
					int nssss= 1;
					continue;
				}
				if( nSize > 2999 ) nSize = 2999;
				SetPos( nStartPos );
				fread( sTemp, sizeof(char),nSize,m_pFile);
				sTemp[nSize] = '\0';
				sReadBuf = sTemp;
				sReadBuf.Trim();
				SetPos( nEndPos-1 );
				return true;
			}
			nNowCount ++;
		}
		// -------------
		// ������ ã������ ����. �׷��� ���� ������ �� �ѹ����̴�.
		long nEndPos = GetEndPos();
		long nSize = nStartPos - nEndPos;
		if( nSize <= 0 ) return false;
		if( nSize > 2999 ) nSize = 2999;
		SetPos( nStartPos );
		fread( sTemp, sizeof(char),nSize,m_pFile);
		sTemp[nSize] = '\0';
		sReadBuf = sTemp;
		sReadBuf.Trim();
		return true;
		*/
	}

	//////////////////////////////////////////////////////////
	// �� ���带 �о�´�.
	long CFileUtil::ReadWord( CString& sReadBuf )
	{
		if( IsOpen() == false ) return -1;
		// -----
		char *plsCuttingChar;
		CString *plsReadTemp;
		long *plsAfterPos;
		// -----
		// ���̸� �������� ô���� ���ڵ��� �����ϰ� ����� �������� ġ��ȭ�Ѵ�.
		plsCuttingChar = new char[3];
		plsReadTemp = new CString[3];
		plsAfterPos = new long[3];
		plsCuttingChar[0] = '\t';
		plsCuttingChar[0] = '\t';
		plsCuttingChar[0] = '\t';
		plsAfterPos[0] = 0;
		plsAfterPos[1] = 0;
		plsAfterPos[2] = 0;
		
		// ������ ���ڱ����� ���ڿ����� �о�´�.
		long nNowPos = GetPos();
		int nReadIndex;
		for( nReadIndex = 0 ; nReadIndex < 3 ; nReadIndex ++ )
		{
			SetPos(nNowPos);
			_ReadToChar( plsCuttingChar[nReadIndex], plsReadTemp[nReadIndex] , true );
			plsAfterPos[nReadIndex] = GetPos();
		}
		
		// �о���ΰ��� ������������ã�´�.
		sReadBuf = "";
		long nNowLength = 0;
		int nUseIndex = -1;
		for( nReadIndex = 0 ; nReadIndex < 3 ; nReadIndex ++ )
		{
			long nReadL = plsReadTemp[nReadIndex].GetLength();
			if( nReadL > 0 && nReadL < nNowLength )
			{
				sReadBuf = plsReadTemp[nReadIndex];
				nNowLength = nReadL;
				nUseIndex = nReadIndex;
			}
		}
		// �о���� ���̸� �����Ѵ�.
		if( nUseIndex >= 0 ) SetPos( plsAfterPos[nUseIndex] );

		// �Ҵ���� ���� �����
		delete [] plsCuttingChar;
		delete [] plsReadTemp;
		delete [] plsAfterPos;

		return nNowLength;	
	}

	//////////////////////////////////////////////////////////
	// �� ���ڿ��� ���ö����� �о�´�.
	long CFileUtil::ReadToEndString( CString sEndString, CString& sReadBuf )		
	{
		const long nOneBlockSize = 3000;	// 
		// ã�� ���ڿ� �̻��� ũ���� ����ũ�⸦ ���Ѵ�.
		long nSearchStringLength = sEndString.GetLength();
		long nBufSize = nOneBlockSize;
		while( true )
		{
			if( nSearchStringLength < nBufSize / 2 ) break;
			nBufSize += nOneBlockSize;
		}
		char* pReadBuf;
		pReadBuf = new char[nBufSize+1];
		long nStartPos = GetPos();
		long nReadSize = 0;
		long nEndReadPos = -1;
		long nNowSectionStartPos;

		// ���߿� ã�� ���ڿ��� ���ٸ� Ŀ���� �ٽ� sEndString��ŭ �ǵ����� ���۸�ŭ �ٽ� �о�´�.
		while( true )
		{
			nNowSectionStartPos = GetPos();
			nReadSize = fread( pReadBuf, sizeof(char), nBufSize, m_pFile );
			if( nReadSize == 0 || nReadSize < nSearchStringLength )	// ���̻� ã������ ����. ���ϳ�.
			{
				break;
			}
			pReadBuf[nBufSize] = '\0';
			CString sTemp;
			sTemp = pReadBuf;
			nEndReadPos = sTemp.Find( sEndString );
			if( nEndReadPos < 0 )
			{
				// �׸��� �ٽ� ��ó�� �ݺ��ؼ� ã�´�.
				SetPos( nNowSectionStartPos + nReadSize - nSearchStringLength );
				continue;
			}
            
			break;
		}
		
		// ���� sEndString�� ã���� ���ٸ� Ŀ���� ó�� ��ġ�� �ǵ����� ���и� �ǵ�����.
		if( nEndReadPos < 0 ) 
		{
			SetPos( nStartPos );
			delete [] pReadBuf;
			return -1;
		}
		// ã�Ҵٸ�.
		// �׸��� sEndString �������� �а� Ŀ���� sEndString�� ������ �������� ��´�.
		nEndReadPos = nNowSectionStartPos + nEndReadPos;
		nReadSize = ReadSection( nStartPos, nEndReadPos, sReadBuf );
		nEndReadPos += nSearchStringLength;
		SetPos( nEndReadPos );
		delete [] pReadBuf;
		return nReadSize;
	}

	// �� ���ڿ��� ���ö����� �о�´�.
	long CFileUtil::ReadToEndString2( CString sEndString, CString& sReadBuf )
	{
		long nPos = GetPos();
		long nReadEndPos = -1;
		int nSearchStringLength = sEndString.GetLength();
		while( true )
		{
			if( IsNowEndPos() == true ) break;

			long nLastPos = GetPos();

			CString sLineStringBuf;
			if( ReadLine(sLineStringBuf) <= 0 )
			{
				if( nLastPos == GetPos() )
				{
					break;
				}
				continue;
			}
			int nPosInLine = sLineStringBuf.Find( sEndString );
			if( nPosInLine < 0 ) continue;
			nReadEndPos = nLastPos + nPosInLine;
			break;
		}
		if( nReadEndPos < 0 ) 
		{
			SetPos( nPos );
			return -1;
		}
		// ã�Ҵٸ�.
		// �׸��� sEndString �������� �а� Ŀ���� sEndString�� ������ �������� ��´�.
		int nReadSize = ReadSection( nPos, nReadEndPos, sReadBuf );
		nPos = GetPos();
		nPos += nSearchStringLength;
		SetPos( nPos );
		return nReadSize;

	}

	///////////////////////////////////////////////////////////////////////////////////////////
	// ���س��� ������ ������ �о�ɴϴ�.
	long CFileUtil::ReadSection( long nSectionStartPos, long nSectionEndPos, CString &sReadBuf )
	{
		if( IsOpen() == false ) return -1;
		char *pReadBuf;
		long nEndPos = GetEndPos();
		if( nEndPos < nSectionEndPos ) nSectionEndPos = nEndPos;
		long nBufSize = nSectionEndPos - nSectionStartPos;
		pReadBuf = new char[nBufSize + 1];

		SetPos( nSectionStartPos );
		long nReadSize = fread( pReadBuf, sizeof(char), nBufSize, m_pFile );
		pReadBuf[nBufSize] = '\0';
		sReadBuf = pReadBuf;
		delete [] pReadBuf;
		return nReadSize;
	}
							
	long CFileUtil::ReadSection( long nSectionStartPos, long nSectionEndPos, char* &pReadBuf )
	{
		if( IsOpen() == false ) return -1;		
		long nEndPos = GetEndPos();
		if( nEndPos < nSectionEndPos ) nSectionEndPos = nEndPos;
		long nBufSize = nSectionEndPos - nSectionStartPos;		

		SetPos( nSectionStartPos );
		long nReadSize = fread( pReadBuf, sizeof(char), nBufSize , m_pFile );
		pReadBuf[nBufSize] = '\0';		
		return nReadSize;
	}
    
	//////////////////////////////////////////////////////////
	// ������ ����.
	bool CFileUtil::WriteLine( CString sWriteBuf )
	{
		long nSize = sWriteBuf.GetLength();
		sWriteBuf += "\n";
		
		long nWriteSize = fwrite( sWriteBuf.GetBuffer(), nSize+1, 1, m_pFile );

		if( nWriteSize <= 0 ) return false;
		return true;
	}

	//////////////////////////////////////////////////////////
	//
	bool CFileUtil::Write( CString sWriteBuf )						 
	{
		long nSize = sWriteBuf.GetLength();
		if( nSize == 0 ) return false;
		
		long nWriteSize = fwrite( sWriteBuf.GetBuffer(), nSize, 1, m_pFile );

		if( nWriteSize <= 0 ) return false;
		return true;
	}


	// ====================================
	//////////////////////////////////////////////////////////
	// ���� ��ġ
	long CFileUtil::GetPos()
	{
		if( IsOpen() == false ) return -1;
		return ftell( m_pFile );
	}

	//////////////////////////////////////////////////////////
	// ��ġ ���� : ���ϰ��� �̵��İ�
	long CFileUtil::SetPos(long nPos)			
	{
		if( IsOpen() == false ) return -1;
		fseek( m_pFile, nPos, SEEK_SET );
		return GetPos();
	}

	//////////////////////////////////////////////////////////
	// ��ġ �̵� : ���ϰ��� �̵��İ�
	long CFileUtil::MovePos(long nMovePos)									
	{
		if( IsOpen() == false ) return -1;
		fseek( m_pFile, nMovePos, SEEK_CUR );
		return GetPos();
	}

	//////////////////////////////////////////////////////////
	// ������ �� ��ġ
	long CFileUtil::GetEndPos()												
	{
		if( IsOpen() == false ) return -1;
		long nNowPos = GetPos();
		fseek( m_pFile, 0, SEEK_END );
		long nEndPos = GetPos();
		SetPos( nNowPos );
		return nEndPos;
	}

	//////////////////////////////////////////////////////////
	// cCutting���� ���ڿ��� �н��ϴ�.
	long CFileUtil::_ReadToChar( char cCuttingChar, CString& sReadBuf , bool bEndToRead )
	{
		if( IsOpen() == false ) return -1;
	
		long nStartPos = GetPos();

		char sTemp[3000];
		
		int nNowCount = 0;
		while( IsNowEndPos() == false )
		{
			long nReadSize = fread(sTemp,sizeof(char),1,m_pFile);
			if( nReadSize <= 0 ) 
			{
				long nsisisis = -1;
			}
			long fPosTemp = GetPos();
			if( sTemp[0] == cCuttingChar && nNowCount > 0 )
			{
				long nEndPos = GetPos();
				long nSize = nEndPos - nStartPos - 1;
				if( nSize <= 0 )
				{	
	//				fseek
					int nssss= 1;
					continue;
				}
				if( nSize > 2999 ) nSize = 2999;
				SetPos( nStartPos );
				fread( sTemp, sizeof(char),nSize,m_pFile);
				sTemp[nSize] = '\0';
				sReadBuf = sTemp;
				sReadBuf.Trim();
				if( bEndToRead == true )	// ���� ������ ���ٸ� ��� �д´�.
				{
					if( sReadBuf != "" ) 
					{
						SetPos( nEndPos-1 );
						return ( GetPos() - nStartPos );
					}
				}
				else
				{
					SetPos( nEndPos-1 );
					return ( GetPos() - nStartPos );
				}
			}
			nNowCount ++;
		}
		// -------------
		// ������ ã������ ����. �׷��� ���� ������ �� �ѹ����̴�.
		long nEndPos = GetEndPos();
		long nSize = nStartPos - nEndPos;
		if( nSize <= 0 ) return -1;
		if( nSize > 2999 ) nSize = 2999;
		SetPos( nStartPos );
		fread( sTemp, sizeof(char), nSize, m_pFile);
		sTemp[nSize] = '\0';
		sReadBuf = sTemp;
		sReadBuf.Trim();
		return ( GetPos() - nStartPos );
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// �����̸��� �и����ִ� �Լ��Դϴ�.
	bool CFileUtil::CuttingFilePathNameAndExt( CString sFullName, CString& sFileName, CString& sFileExt, CString& sFilePath )
	{
		if( sFullName == "" ) 
		{
			sFileName = "";
			sFilePath = "";
			sFileExt = "";
			return true;
		}
		
		int nLastDotIndex = sFullName.ReverseFind('.');
		
		int nLastInverseSlashIndex = sFullName.ReverseFind('\\');
		CString sLeftString = sFullName;

		// Ȯ����
		if( nLastDotIndex <= nLastInverseSlashIndex )	// ���� �������� �Ѵ� ��ã���� ���
		{
			sFileExt = "";
		}
		else
		{
			sFileExt = sFullName.Right(sFullName.GetLength() - nLastDotIndex - 1);
			sLeftString = sFullName.Left(nLastDotIndex);
		}

		if( nLastInverseSlashIndex < 0 )
		{
			sFileName = sLeftString;
			sFilePath = "";
		}
		else
		{
			sFileName = sLeftString.Right(sLeftString.GetLength() - nLastInverseSlashIndex - 1);
			sFilePath = sLeftString.Left(nLastInverseSlashIndex+1);
		}
		
		return true;
	}				

	bool CFileUtil::WriteLineToCFile( CFile& file, CString sWriteString,bool bIsLast)
	{
		char CR=0x0d;	
		char LF=0x0a;

		sWriteString.TrimRight();
		if(sWriteString.GetLength() == 0) sWriteString = "NULL"; 
	
		file.Write(sWriteString.GetBuffer(0), sWriteString.GetLength());
		if (bIsLast == false) 
		{
			file.Write(&CR, 1);		
			file.Write(&LF, 1);
		}
		return true;
	}
};