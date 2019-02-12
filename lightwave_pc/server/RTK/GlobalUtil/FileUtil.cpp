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
	// 현재 파일을 열고있으면 이름을 설정할수 없다.
	bool CFileUtil::SetFileName( CString sFileName )
	{
		if( m_pFile != NULL ) return false;
		m_sFileName = sFileName;
		return true;
	}

	//////////////////////////////////////////////////////////
	// 열기 옵션 선택 ( 현재파일이 열려있으면 설정할수 없음 )
	bool CFileUtil::SetFileOpenMode( CString sOption )
	{
		if( m_pFile != NULL ) return false;
		m_sFileOption = sOption;
		return true;
	}

	//////////////////////////////////////////////////////////
	// 파일 열기
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
	// 파일 열기
	bool CFileUtil::FileOpen()
	{
		if( m_sFileName == "" || m_sFileOption == "" ) return false;
		m_pFile = fopen( m_sFileName, m_sFileOption );
		if( m_pFile == NULL ) return false;
		return true;
	}

	//////////////////////////////////////////////////////////
	// 파일 닫기
	bool CFileUtil::FileClose()
	{
		if( m_pFile == NULL ) return false;
		fclose( m_pFile );
		m_pFile = NULL;
		return true;
	}

	// 파일의 끝인지를 물어봅니다.
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
	// 현재 열려있는지 확인합니다.
	bool CFileUtil::IsOpen()
	{
		if( m_pFile == NULL ) return false;
		return true;
	}


	// ====================================
	//////////////////////////////////////////////////////////
	// 한가지 블럭문자열로 앞뒤가 구분되어있는 블럭을 가져온다.
	bool CFileUtil::ReadBlock( CString sBlock, CString& sReadBuf )				
	{
		return ReadBlock(sBlock, sBlock, sReadBuf );
	}

	//////////////////////////////////////////////////////////
	// 앞뒤로 다른 블럭문자열로 구분되어잇는 블럭을 가져온다.
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
			if( bOpenBlock == false )	// 아직 BlockStartString을 찾기전
			{
				if( sSBlock == sBuf )
				{
					bOpenBlock = true;
				}
			}
			else						// BlockStartString을 찾은후 sBlockEndString을 찾기전
			{
				if( sEBlock == sBuf )
				{
					sReadBuf = sSavingTemp;	// 검색이 끝낫다면 현재까지 찾은 내용을 넘겨주고 
					return true;				// true 리턴
				}
				else
				{
					if( sSavingTemp.GetLength() > 0 ) sSavingTemp = sSavingTemp + "\n";
					sSavingTemp = sSavingTemp + sBuf;
				}
			}
		}
		// 찾기 실패하였다.( 커서를 함수시작할때의 위치로 되돌린다. )
		SetPos( nStartPosition );
		return false;
	}

	//////////////////////////////////////////////////////////
	// 한 라인을 읽어온다.
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
		// 끝까지 찾앗지만 없다. 그러니 남은 문장이 다 한문장이다.
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
	// 한 워드를 읽어온다.
	long CFileUtil::ReadWord( CString& sReadBuf )
	{
		if( IsOpen() == false ) return -1;
		// -----
		char *plsCuttingChar;
		CString *plsReadTemp;
		long *plsAfterPos;
		// -----
		// 길이를 가져오는 척도의 문자들을 세팅하고 사용할 변수들을 치고화한다.
		plsCuttingChar = new char[3];
		plsReadTemp = new CString[3];
		plsAfterPos = new long[3];
		plsCuttingChar[0] = '\t';
		plsCuttingChar[0] = '\t';
		plsCuttingChar[0] = '\t';
		plsAfterPos[0] = 0;
		plsAfterPos[1] = 0;
		plsAfterPos[2] = 0;
		
		// 정해진 문자까지의 문자열들을 읽어온다.
		long nNowPos = GetPos();
		int nReadIndex;
		for( nReadIndex = 0 ; nReadIndex < 3 ; nReadIndex ++ )
		{
			SetPos(nNowPos);
			_ReadToChar( plsCuttingChar[nReadIndex], plsReadTemp[nReadIndex] , true );
			plsAfterPos[nReadIndex] = GetPos();
		}
		
		// 읽어들인것중 가장작은것을찾는다.
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
		// 읽어들인 길이를 리턴한다.
		if( nUseIndex >= 0 ) SetPos( plsAfterPos[nUseIndex] );

		// 할당받은 버퍼 지우기
		delete [] plsCuttingChar;
		delete [] plsReadTemp;
		delete [] plsAfterPos;

		return nNowLength;	
	}

	//////////////////////////////////////////////////////////
	// 한 문자열이 나올때까지 읽어온다.
	long CFileUtil::ReadToEndString( CString sEndString, CString& sReadBuf )		
	{
		const long nOneBlockSize = 3000;	// 
		// 찾을 문자열 이상의 크기의 버퍼크기를 정한다.
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

		// 그중에 찾는 문자열이 없다면 커서를 다시 sEndString만큼 되돌리고 버퍼만큼 다시 읽어온다.
		while( true )
		{
			nNowSectionStartPos = GetPos();
			nReadSize = fread( pReadBuf, sizeof(char), nBufSize, m_pFile );
			if( nReadSize == 0 || nReadSize < nSearchStringLength )	// 더이상 찾을것이 없다. 파일끝.
			{
				break;
			}
			pReadBuf[nBufSize] = '\0';
			CString sTemp;
			sTemp = pReadBuf;
			nEndReadPos = sTemp.Find( sEndString );
			if( nEndReadPos < 0 )
			{
				// 그리고 다시 윗처럼 반복해서 찾는다.
				SetPos( nNowSectionStartPos + nReadSize - nSearchStringLength );
				continue;
			}
            
			break;
		}
		
		// 만약 sEndString을 찾을수 없다면 커서는 처음 위치로 되돌리고 실패를 되돌린다.
		if( nEndReadPos < 0 ) 
		{
			SetPos( nStartPos );
			delete [] pReadBuf;
			return -1;
		}
		// 찾았다면.
		// 그리고 sEndString 이전까지 읽고 커서는 sEndString이 끝나는 지접으로 잡는다.
		nEndReadPos = nNowSectionStartPos + nEndReadPos;
		nReadSize = ReadSection( nStartPos, nEndReadPos, sReadBuf );
		nEndReadPos += nSearchStringLength;
		SetPos( nEndReadPos );
		delete [] pReadBuf;
		return nReadSize;
	}

	// 한 문자열이 나올때까지 읽어온다.
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
		// 찾았다면.
		// 그리고 sEndString 이전까지 읽고 커서는 sEndString이 끝나는 지접으로 잡는다.
		int nReadSize = ReadSection( nPos, nReadEndPos, sReadBuf );
		nPos = GetPos();
		nPos += nSearchStringLength;
		SetPos( nPos );
		return nReadSize;

	}

	///////////////////////////////////////////////////////////////////////////////////////////
	// 정해놓은 구간의 내용을 읽어옵니다.
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
	// 한줄을 쓴다.
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
	// 현재 위치
	long CFileUtil::GetPos()
	{
		if( IsOpen() == false ) return -1;
		return ftell( m_pFile );
	}

	//////////////////////////////////////////////////////////
	// 위치 설정 : 리턴값은 이동후값
	long CFileUtil::SetPos(long nPos)			
	{
		if( IsOpen() == false ) return -1;
		fseek( m_pFile, nPos, SEEK_SET );
		return GetPos();
	}

	//////////////////////////////////////////////////////////
	// 위치 이동 : 리턴값은 이동후값
	long CFileUtil::MovePos(long nMovePos)									
	{
		if( IsOpen() == false ) return -1;
		fseek( m_pFile, nMovePos, SEEK_CUR );
		return GetPos();
	}

	//////////////////////////////////////////////////////////
	// 파일의 끝 위치
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
	// cCutting까지 문자열을 읽습니다.
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
				if( bEndToRead == true )	// 읽은 내용이 없다면 계속 읽는다.
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
		// 끝까지 찾앗지만 없다. 그러니 남은 문장이 다 한문장이다.
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
	// 파일이름을 분리해주는 함수입니다.
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

		// 확장자
		if( nLastDotIndex <= nLastInverseSlashIndex )	// 둘이 같을경우는 둘다 못찾았을 경우
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