#pragma once

namespace GlobalUtil
{
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@	
	// 파일과 관련된 여러가지 유용한 기능을 제공한다.
	class CFileUtil
	{
	protected:
		FILE* m_pFile;
		CString m_sFileName;
		CString m_sFileOption;

	public:
		CFileUtil();
		~CFileUtil();

		bool SetFilePointer( FILE *pFile , bool bClose = true );
		bool SetFileName( CString sFileName );										// 현재 파일을 열고있으면 이름을 설정할수 없다.
		bool SetFileOpenMode( CString sOption );									// 열기 옵션 선택 ( 현재파일이 열려있으면 설정할수 없음 )
		bool FileOpen(CString sFileName, CString sFileOption);						// 파일 열기
		bool FileOpen();															// 파일 열기
		bool FileClose();															// 파일 닫기

		// ====================================
		bool IsOpen();																// 현재 열려있는지 확인합니다.
		bool IsNowEndPos();															// 파일의 끝인지를 물어봅니다.

		// ====================================
		bool ReadBlock( CString sBlock, CString& sReadBuf );						// 한가지 블럭문자열로 앞뒤가 구분되어있는 블럭을 가져온다.
		bool ReadBlock( CString sSBlock, CString sEBlock, CString& sReadBuf );		// 앞뒤로 다른 블럭문자열로 구분되어잇는 블럭을 가져온다.
		long ReadLine( CString& sReadBuf );											// 한 라인을 읽어온다.
		long ReadWord( CString& sReadBuf );											// 한 워드를 읽어온다.
		long ReadToEndString( CString sEndString, CString& sReadBuf );				// 한 문자열이 나올때까지 읽어온다.
		long ReadToEndString2( CString sEndString, CString& sReadBuf );				// 한 문자열이 나올때까지 읽어온다.
		long ReadSection( long nSectionStartPos, long nSectionEndPos, CString &sReadBuf );
																					// 정해놓은 구간의 내용을 읽어옵니다.
		long ReadSection( long nSectionStartPos, long nSectionEndPos, char* &pReadBuf );
        
		bool WriteLine( CString sWriteBuf );										// 한줄을 쓴다.
		bool Write( CString sWriteBuf );											// 

		// ====================================
		long GetPos();																// 현재 위치
		long SetPos(long nPos);														// 위치 설정 : 리턴값은 이동후값
		long MovePos(long nMovePos);												// 위치 이동 : 리턴값은 이동후값
		long GetEndPos();															// 파일의 끝 위치
			
	protected:
		long _ReadToChar( char cCuttingChar, CString& sReadBuf , bool bEndToRead = false );
																					// cCutting까지 문자열을 읽습니다.

		//==========================================================================================================================
		// 지원 함수
	public:
		static bool CuttingFilePathNameAndExt( CString sFullName, CString& sFileName, CString& sFileExt, CString& sFilePath );
																					// 파일이름을 분리해주는 함수입니다.

		// = CFile지원 함수 =
		static bool WriteLineToCFile( CFile& file, CString sWriteString,bool bIsLast = false);
	};
};