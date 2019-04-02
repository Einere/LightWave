#include "stdafx.h"
#include <ctime>
#include <chrono>
#include "Shape/DS_Polygon.h"
#include "json.h"
#include "json/json.h"
#include "Task.h"

using namespace File;
using namespace DataType;
using namespace DataType::ShapeType;

namespace SurveyTask {
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

	const std::vector<ParcelToStore>& Task::getParcels() const
	{
		return m_parcels;
	}

	void Task::clearParcelPoints()
	{
		m_parcels.clear();
	}

	int Task::addParcels(std::vector<CParcel> pts)
	{
		for (int i = 0; i < pts.size(); ++i) {
			ParcelToStore parcel = Parcel2ParcelToStore(pts[i]);
			m_parcels.push_back(parcel);
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
		for (ParcelToStore& parcel : m_parcels) {
			Json::Value parcelRoot;
			parcelRoot["landNo"] = (LPCTSTR)parcel.landNo;
			parcelRoot["parcelPoints"] = Json::Value(Json::arrayValue);

			const int pointCount = parcel.points.size();
			for (int i = 0; i < pointCount; ++i) {
				Json::Value pointRoot;
				pointRoot["X"] = parcel.points[i].first;
				pointRoot["Y"] = parcel.points[i].second;
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
		Json::Value json = Json::parse(data);
		assert(json != Json::nullValue);

		setId(json["id"].asUInt());
		setTaskName(json["taskName"].asCString());
		setTaskDesc(json["taskDesc"].asCString());
		setLotNumber(json["lotNumber"].asCString());
		setFileName(json["fileName"].asCString());

		Json::Value parcels(Json::arrayValue);
		parcels = json["parcels"];
		Json::ArrayIndex size = parcels.size();
		for (int i = 0; i < size; ++i) {
			ParcelToStore parcel;
			Json::Value jsonParcel = json["parcels"][i];
			parcel.landNo = jsonParcel["landNo"].asCString();

			Json::ArrayIndex size = jsonParcel["parcelPoints"].size();
			for (int i = 0; i < size; ++i) {
				parcel.points[i].first = jsonParcel["parcelPoints"]["X"].asDouble();
				parcel.points[i].second = jsonParcel["parcelPoints"]["Y"].asDouble();
			}

			m_parcels.push_back(parcel);
		}

		return TRUE;
	}

	UINT Task::generateId() const
	{
		return (UINT)time(NULL);
	}

	ParcelToStore Parcel2ParcelToStore(DataType::CParcel& parcel)
	{
		ParcelToStore parcelToStore;

		parcelToStore.landNo = parcel.GetLandNo();

		CDS_Polygon shape = parcel.GetParcelShape();
		CDS_Polyline* line = shape.GetPolyline(0);
		const int pointCount = line->GetPointCount();
		for (int i = 0; i < pointCount; ++i) {
			CDS_Point pt = line->GetPoint(i);
			parcelToStore.points.push_back({ pt.GetX(), pt.GetY() });
		}

		return parcelToStore;
	}
}