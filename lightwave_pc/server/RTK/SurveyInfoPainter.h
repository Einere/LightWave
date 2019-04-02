#pragma once

#include "Survey.h"

class SurveyInfoPainter
{
public:
	SurveyInfoPainter();
	~SurveyInfoPainter();

	void setHwnd(HWND hwnd);

	void DrawServeyInfo(double x, double y, Survey survey);
	void DrawServeyPoint(double x, double y);
private:
	HWND m_hTargetWnd;
};

