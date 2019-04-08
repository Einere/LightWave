#include "stdafx.h"
#include "SurveyInfoPainter.h"


SurveyInfoPainter::SurveyInfoPainter()
{
}


SurveyInfoPainter::~SurveyInfoPainter()
{
}

void SurveyInfoPainter::setHwnd(HWND hwnd)
{
	m_hTargetWnd = hwnd;
}

void SurveyInfoPainter::DrawServeyInfo(double x, double y, SurveyTask::Survey survey)
{
	DrawServeyPoint(x, y);
}

void SurveyInfoPainter::DrawServeyPoint(double x, double y)
{
	/*
		TODO: 투명한 창을 지도 위에 띄워 정보를 표시하도록 개선

		cadapi가 지도를 그릴 때마다 내가 그린 점들을 지운다.
		지도 윈도우에 직접 그리는 것은 힘들 것으로 생각됨.
	*/
	char msgBuf[50];
	sprintf(msgBuf, "%f, %f에 그리기를 시작합니다", x, y);
	MessageBox(NULL, msgBuf, NULL, MB_OK);
	HDC hdc = ::GetWindowDC(m_hTargetWnd);

	CPen pen;
	pen.CreatePen(PS_SOLID, 100, RGB(255, 0, 0));
	SelectObject(hdc, pen);

	MoveToEx(hdc, x, y, NULL);
	LineTo(hdc, x + 10, y + 10);
	
}
