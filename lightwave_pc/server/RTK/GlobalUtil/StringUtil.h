#pragma once

namespace GlobalUtil
{
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// ��Ʋ�� ���õ� �������� ������ ����� �����Ѵ�.
	class CStringUtil
	{
	protected:
		CStringUtil(void);
		~CStringUtil(void);

	public:
		static int CuttingStringToList( CString sOriginalString, CString sCuttingToken, CArray<CString>& lsAfterList );

	};
};
