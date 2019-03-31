#pragma once

#include "./Shape/DS_Point.h"

class Survey : public DataType::ShapeType::CDS_Point
{
public:
	Survey();
	Survey(double fX, double fY);
	Survey(const Survey& Source);
	~Survey();

	// TODO: 이미지 반환하는 Getter 선언

private:
	// TODO: 이미지를 담는 필드 선언
};

