#include "stdafx.h"
#include <ctime>
#include <chrono>
#include "Shape/DS_Polygon.h"
#include "json/json.h"
#include "Task.h"

using namespace File;
using namespace DataType;
using namespace DataType::ShapeType;

Task::Task()
{
	m_id = generateId();
}

CString Task::getTaskName() const
{
	return m_taskName;
}

void Task::setTaskName(CString taskName)
{
	m_taskName = taskName;
}

CString Task::getTaskDesc() const
{
	return m_taskDesc;
}

void Task::setTaskDesc(CString taskDesc)
{
	m_taskDesc = taskDesc;
}

CString Task::getFileName() const
{
	return m_fileName;
}

void Task::setFileName(CString fileName)
{
	m_fileName = fileName;
}

CString Task::getLotNumber() const
{
	return m_lotNumber;
}

void Task::setLotNumber(CString lotNumber)
{
	m_lotNumber = lotNumber;
}

UINT Task::getId() const
{
	return m_id;
}

void Task::setId(UINT id)
{
	m_id = id;
}

const std::vector<std::reference_wrapper<DataType::CParcel>>& Task::getParcels() const
{
	return m_parcels;
}

void Task::clearParcelPoints()
{
	m_parcels.clear();
}

int Task::addParcels(std::vector<std::reference_wrapper<DataType::CParcel>> pts)
{
	for (int i = 0; i < pts.size(); ++i) {
		m_parcels.push_back(pts[i]);
	}
	return m_parcels.size();
}

CString Task::toFileContent()
{
	/* 저장할 필드 목록: [id, taskName, taskDesc, lotNumber, fileName, parcelPoints]	*/
	Json::Value root;
	root["id"] = m_id;
	root["taskName"] = (LPCTSTR)m_taskName;
	root["taskDesc"] = (LPCTSTR)m_taskDesc;
	root["lotNumber"] = (LPCTSTR)m_lotNumber;
	root["fileName"] = (LPCTSTR)m_fileName;

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
	CString path;
	path.Format("%s/%s/%s.tsk", rootDir, m_taskName, m_taskName);
	return path;
}

BOOL Task::resolveFileData(const char* data)
{
	return FALSE;
}

UINT Task::generateId() const
{
	return (UINT)time(NULL);
}
