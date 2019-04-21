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
		// TODO: 이미지 반환하는 Getter 선언

	private:
		CString m_memo;
		// TODO: 이미지를 담는 필드 선언
	};
}