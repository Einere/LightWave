#pragma once

#include "./Shape/DS_Point.h"

namespace SurveyTask {
	class Survey : public DataType::ShapeType::CDS_Point
	{
	public:
		Survey();
		Survey(double fX, double fY);
		//Survey(const Survey& Source);
		~Survey();

		void setMemo(CString memo);
		CString getMemo() const;
		// TODO: �̹��� ��ȯ�ϴ� Getter ����

	private:
		CString m_memo;
		// TODO: �̹����� ��� �ʵ� ����
	};
}