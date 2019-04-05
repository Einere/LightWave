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
		TODO: ������ â�� ���� ���� ��� ������ ǥ���ϵ��� ����

		cadapi�� ������ �׸� ������ ���� �׸� ������ �����.
		���� �����쿡 ���� �׸��� ���� ���� ������ ������.
	*/
	char msgBuf[50];
	sprintf(msgBuf, "%f, %f�� �׸��⸦ �����մϴ�", x, y);
	MessageBox(NULL, msgBuf, NULL, MB_OK);
	HDC hdc = ::GetWindowDC(m_hTargetWnd);

	CPen pen;
	pen.CreatePen(PS_SOLID, 100, RGB(255, 0, 0));
	SelectObject(hdc, pen);

	MoveToEx(hdc, x, y, NULL);
	LineTo(hdc, x + 10, y + 10);
	
}
