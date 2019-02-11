#include "StdAfx.h"
#include "StringUtil.h"


namespace GlobalUtil
{
	CStringUtil::CStringUtil(void)
	{
	}


	CStringUtil::~CStringUtil(void)
	{
	}

	int CStringUtil::CuttingStringToList( CString sOriginalString, CString sCuttingToken, CArray<CString>& lsAfterList )
	{
		int nSearchPosition = 0;
		CString sLeft = sOriginalString;
		int nTokenSize = sCuttingToken.GetLength();
		while( true )
		{
			int nIndex = sLeft.Find(sCuttingToken);
			if( nIndex < 0 ) 
			{
				lsAfterList.Add( sLeft );
				break;
			}
			CString sReadBuf;
			if( nIndex == 0 )
			{
				sReadBuf = "";
			}
			else
			{
				sReadBuf = sLeft.Left( nIndex );
			}
			int nLeftLength = sLeft.GetLength() -  ( nIndex + nTokenSize );
			if( nLeftLength > 0 )
			{
				sLeft = sLeft.Right( nLeftLength );
			}
			else
			{
				sLeft = "";
			}
			lsAfterList.Add( sReadBuf );
		}


		return lsAfterList.GetCount();
	}
};