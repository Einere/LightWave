#include "stdafx.h"
#include <ctime>
#include <chrono>
#include "Shape/DS_Polygon.h"
#include "json.h"
#include "json/json.h"
#include "Task.h"
#include "path.h"

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

	BOOL Task::saveImage(const CString byteInStr, const CString fileName)
	{
		CString path;
		CString dirPath = Path::getDirPath(srcPath);
		path.Format("%s/%s", dirPath, fileName);

		CFile file;
		const bool isOpenSucceed = file.Open(path, CFile::modeWrite | CFile::modeCreate);
		assert(isOpenSucceed);

		file.Write((void*)byteInStr.GetString(), byteInStr.GetLength());
		file.Close();

		return TRUE;
	}

	BOOL Task::hasStarted() const
	{
		return m_hasStarted;
	}

	BOOL Task::start()
	{
		if (m_hasStarted) return FALSE;
		
		return (m_hasStarted = TRUE);
	}

	BOOL Task::stop()
	{
		if (!m_hasStarted) return FALSE;

		return (m_hasStarted = FALSE);
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

	Json::Value Task::toJson()
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

		return root;
	}

	CString Task::toFileContent()
	{
		auto jsonInString = Json::json2Str(toJson());
		return jsonInString.c_str();
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
				double x = jsonParcel["parcelPoints"][i]["X"].asDouble();
				double y = jsonParcel["parcelPoints"][i]["Y"].asDouble();
				parcel.points.push_back({ x,y });
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