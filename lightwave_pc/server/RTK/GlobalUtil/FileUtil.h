#pragma once

namespace GlobalUtil
{
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@	
	// ���ϰ� ���õ� �������� ������ ����� �����Ѵ�.
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
		bool SetFileName( CString sFileName );										// ���� ������ ���������� �̸��� �����Ҽ� ����.
		bool SetFileOpenMode( CString sOption );									// ���� �ɼ� ���� ( ���������� ���������� �����Ҽ� ���� )
		bool FileOpen(CString sFileName, CString sFileOption);						// ���� ����
		bool FileOpen();															// ���� ����
		bool FileClose();															// ���� �ݱ�

		// ====================================
		bool IsOpen();																// ���� �����ִ��� Ȯ���մϴ�.
		bool IsNowEndPos();															// ������ �������� ����ϴ�.

		// ====================================
		bool ReadBlock( CString sBlock, CString& sReadBuf );						// �Ѱ��� �����ڿ��� �յڰ� ���еǾ��ִ� ���� �����´�.
		bool ReadBlock( CString sSBlock, CString sEBlock, CString& sReadBuf );		// �յڷ� �ٸ� �����ڿ��� ���еǾ��մ� ���� �����´�.
		long ReadLine( CString& sReadBuf );											// �� ������ �о�´�.
		long ReadWord( CString& sReadBuf );											// �� ���带 �о�´�.
		long ReadToEndString( CString sEndString, CString& sReadBuf );				// �� ���ڿ��� ���ö����� �о�´�.
		long ReadToEndString2( CString sEndString, CString& sReadBuf );				// �� ���ڿ��� ���ö����� �о�´�.
		long ReadSection( long nSectionStartPos, long nSectionEndPos, CString &sReadBuf );
																					// ���س��� ������ ������ �о�ɴϴ�.
		long ReadSection( long nSectionStartPos, long nSectionEndPos, char* &pReadBuf );
        
		bool WriteLine( CString sWriteBuf );										// ������ ����.
		bool Write( CString sWriteBuf );											// 

		// ====================================
		long GetPos();																// ���� ��ġ
		long SetPos(long nPos);														// ��ġ ���� : ���ϰ��� �̵��İ�
		long MovePos(long nMovePos);												// ��ġ �̵� : ���ϰ��� �̵��İ�
		long GetEndPos();															// ������ �� ��ġ
			
	protected:
		long _ReadToChar( char cCuttingChar, CString& sReadBuf , bool bEndToRead = false );
																					// cCutting���� ���ڿ��� �н��ϴ�.

		//==========================================================================================================================
		// ���� �Լ�
	public:
		static bool CuttingFilePathNameAndExt( CString sFullName, CString& sFileName, CString& sFileExt, CString& sFilePath );
																					// �����̸��� �и����ִ� �Լ��Դϴ�.

		// = CFile���� �Լ� =
		static bool WriteLineToCFile( CFile& file, CString sWriteString,bool bIsLast = false);
	};
};