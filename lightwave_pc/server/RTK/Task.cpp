#include "stdafx.h"
#include "Shape/DS_Polygon.h"
#include "json/json.h"
#include "Task.h"

using namespace File;
using namespace DataType;
using namespace DataType::ShapeType;

Task::Task()
{
}

Task::Task(const Task & other)
{
	Task::const_iterator itor = other.begin();
	for (; itor != other.end(); ++itor) {
		insert(std::pair<CString, CString>(itor->first, itor->second));
	}

	addParcels(other.m_parcels);
}

const std::vector<std::reference_wrapper<DataType::CParcel>>& Task::getParcels() const
{
	return m_parcels;
}

void Task::clearParcelPoints()
{
	m_parcels.clear();
}
//
//int Task::addParcels(const CParcel* pts, size_t offset, size_t count)
//{
//	assert(pts);
//	for (int i = offset; i < offset + count; ++i) {
//		m_parcels.push_back((CParcel&)pts[i]);
//	}
//
//	return m_parcels.size();
//}

int Task::addParcels(std::vector<std::reference_wrapper<DataType::CParcel>> pts)
{
	for (int i = 0; i < pts.size(); ++i) {
		m_parcels.push_back(pts[i]);
	}
	/*for (auto pt : pts) {
		m_parcels.push_back(pt);
	}*/

	return m_parcels.size();
}

CString Task::toFileContent()
{
	Json::Value root;
	for (auto itor = begin(); itor != end(); ++itor) {
		root[itor->first] = (LPCTSTR)itor->second;
	}

	root["parcels"] = Json::Value(Json::arrayValue);
	for (auto itor = m_parcels.begin(); itor != m_parcels.end(); ++itor) {
		CParcel& parcel = *itor;

		Json::Value parcelRoot;
		parcelRoot["landNo"] = (LPCTSTR)parcel.GetLandNo();
		parcelRoot["parcelPoints"] = Json::Value(Json::arrayValue);

		CDS_Polygon& shape = parcel.GetParcelShape();
		CDS_Polyline* line = shape.GetPolyline(0);
		const int pointCount = line->GetPointCount();
		for (int i = 0; i < pointCount; ++i) {
			Json::Value pointRoot;
			CDS_Point pt = line->GetPoint(i);
			pointRoot["X"] = pt.GetX();
			pointRoot["Y"] = pt.GetY();
			parcelRoot["parcelPoints"].append(pointRoot);
		}
		
		root["parcels"].append(parcelRoot);
	}

	Json::FastWriter writer;
	std::string buf = writer.write(root);
	return buf.c_str();
}

CString Task::getDefaultPath()
{
	CString name = find("name")->second;
	CString path;
	path.Format("%s/%s/%s.tsk", rootDir, name, name);
	return path;
}
