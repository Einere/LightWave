#pragma once

namespace GlobalUtil
{
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// 스틀링 관련된 여러가지 유용한 기능을 제공한다.
	class CStringUtil
	{
	protected:
		CStringUtil(void);
		~CStringUtil(void);

	public:
		static int CuttingStringToList( CString sOriginalString, CString sCuttingToken, CArray<CString>& lsAfterList );

	};
};
