#include "stdafx.h"
#include "Task.h"

const std::vector<CDS_Point>& Task::getParcelPoints() const
{
	return m_parcelPoints;
}

void Task::clearParcelPoints()
{
	m_parcelPoints.clear();
}

int Task::addParcelPoints(const CDS_Point* pts, size_t offset, size_t count)
{
	assert(pts);
	for (int i = offset; i < offset + count; ++i) {
		m_parcelPoints.push_back(pts[i]);
	}

	return m_parcelPoints.size();
}

int Task::addParcelPoints(const std::vector<CDS_Point>& pts)
{
	for (const CDS_Point& pt : pts) {
		m_parcelPoints.push_back(pt);
	}

	return m_parcelPoints.size();
}
