#include "stdafx.h"
#include "Survey.h"

namespace SurveyTask {
	Survey::Survey()
	{
	}

	Survey::Survey(double fX, double fY) : CDS_Point(fX, fY)
	{
	}

	Survey::Survey(const Survey & Source) : CDS_Point(Source)
	{
	}


	Survey::~Survey()
	{
	}

}