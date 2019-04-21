#include "stdafx.h"
#include "Survey.h"

namespace SurveyTask {
	Survey::Survey()
	{
	}

	Survey::Survey(double fX, double fY) : CDS_Point(fX, fY)
	{
	}



	Survey::~Survey()
	{
	}

	void Survey::setMemo(CString memo)
	{
		m_memo = memo;
	}

	CString Survey::getMemo() const
	{
		return m_memo;
	}

}