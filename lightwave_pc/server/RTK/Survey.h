#pragma once

#include "./Shape/DS_Point.h"

class Survey : public DataType::ShapeType::CDS_Point
{
public:
	Survey();
	Survey(double fX, double fY);
	Survey(const Survey& Source);
	~Survey();

	// TODO: �̹��� ��ȯ�ϴ� Getter ����

private:
	// TODO: �̹����� ��� �ʵ� ����
};

