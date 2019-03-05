#pragma once

#include <map>
#include "./Shape/DS_Point.h"

using DataType::ShapeType::CDS_Point;

// 작업을 나타내는 클래스
class Task : public std::map<LPCTSTR, LPCTSTR>{
public:
	const std::vector<CDS_Point>& getParcelPoints() const;

	void clearParcelPoints();
	int addParcelPoints(const CDS_Point* pts, size_t offset, size_t count);
	int addParcelPoints(const std::vector<CDS_Point>& pts);
	//void addParcelPoint(const CDS_Point pt);


private:
	std::vector<CDS_Point> m_parcelPoints;
};