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
		m_id = GenerateId();
		m_ext = "tsk";
	}

	CString Task::GetTaskName() const
	{
		return m_taskName;
	}

	void Task::SetTaskName(CString taskName)
	{
		m_taskName = taskName;
		m_fileName = m_taskName;
		m_parentPath = rootDir + "/" + m_taskName;
	}

	CString Task::GetTaskDesc() const
	{
		return m_taskDesc;
	}

	void Task::SetTaskDesc(CString taskDesc)
	{
		m_taskDesc = taskDesc;
	}

	CString Task::GetCifPath() const
	{
		return m_cifPath;
	}

	void Task::SetCifPath(CString fileName)
	{
		m_cifPath = fileName;
	}

	CString Task::GetLotNumber() const
	{
		return m_lotNumber;
	}

	void Task::SetLotNumber(CString lotNumber)
	{
		m_lotNumber = lotNumber;
	}

	UINT Task::GetId() const
	{
		return m_id;
	}

	void Task::SetId(UINT id)
	{
		m_id = id;
	}

	const std::vector<ParcelToStore>& Task::GetParcels() const
	{
		return m_parcels;
	}

	BOOL Task::HasStarted() const
	{
		return m_hasStarted;
	}

	BOOL Task::Start()
	{
		if (m_hasStarted) return FALSE;
		
		return (m_hasStarted = TRUE);
	}

	BOOL Task::Stop()
	{
		if (!m_hasStarted) return FALSE;

		return (m_hasStarted = FALSE);
	}

	void Task::ClearParcelPoints()
	{
		m_parcels.clear();
	}

	int Task::AddParcels(std::vector<CParcel> pts)
	{
		for (size_t i = 0; i < pts.size(); ++i) {
			ParcelToStore parcel = Parcel2ParcelToStore(pts[i]);
			m_parcels.push_back(parcel);
		}
		return m_parcels.size();
	}

	void Task::RegisterSurvey(Survey survey)
	{
		m_surveys.push_back(survey);
	}

	Survey * Task::GetSurveyById(UINT id)
	{
		int surveysCount = m_surveys.size();
		for (int i = 0; i < surveysCount; ++i) {
			if (id == m_surveys[i].GetId()) {
				return &(m_surveys[i]);
			}
		}

		return NULL;
	}

	const std::vector<Survey>& Task::GetSurveys() const
	{
		return m_surveys;
	}

	Survey * Task::GetSurveyByCoord(double x, double y)
	{
		const int surveysCount = m_surveys.size();
		for (int i = 0; i < surveysCount; ++i) {
			if (x == m_surveys.at(i).GetX() && y == m_surveys[i].GetY()) {
				return &m_surveys[i];
			}
		}
		
		return NULL;
	}

	Json::Value Task::toJson()
	{
		/* 저장할 필드 목록: [id, taskName, taskDesc, lotNumber, fileName, parcels, surveys]	*/
		Json::Value root;
		root["id"] = m_id;
		root["taskName"] = (LPCTSTR)m_taskName;
		root["taskDesc"] = (LPCTSTR)m_taskDesc;
		root["lotNumber"] = (LPCTSTR)m_lotNumber;
		root["fileName"] = (LPCTSTR)m_cifPath;

		root["parcels"] = Json::Value(Json::arrayValue);
		for (ParcelToStore& parcel : m_parcels) {
			root["parcels"].append(Parcel2Json(parcel));
		}

		root["surveys"] = Json::Value(Json::arrayValue);
		for (Survey& survey : m_surveys) {
			root["surveys"].append(survey.ToJson());
		}

		return root;
	}

	std::string Task::ToFileContent()
	{
		auto jsonInString = Json::json2Str(toJson());
		return jsonInString;
	}

	BOOL Task::ResolveFileData(const char* data)
	{
		Json::Value json = Json::parse(data);
		assert(json != Json::nullValue);

		SetId(json["id"].asUInt());
		SetTaskName(json["taskName"].asCString());
		SetTaskDesc(json["taskDesc"].asCString());
		SetLotNumber(json["lotNumber"].asCString());
		SetCifPath(json["fileName"].asCString());

		Json::Value parcels(Json::arrayValue);
		parcels = json["parcels"];
		Json::ArrayIndex size = parcels.size();
		for (Json::ArrayIndex i = 0; i < size; ++i) {
			ParcelToStore parcel;
			Json::Value jsonParcel = json["parcels"][i];
			parcel.landNo = jsonParcel["landNo"].asCString();

			Json::ArrayIndex size = jsonParcel["parcelPoints"].size();
			for (Json::ArrayIndex i = 0; i < size; ++i) {
				double x = jsonParcel["parcelPoints"][i]["X"].asDouble();
				double y = jsonParcel["parcelPoints"][i]["Y"].asDouble();
				parcel.points.push_back({ x,y });
			}

			m_parcels.push_back(parcel);
		}

		Json::Value surveysRoot(Json::arrayValue);
		surveysRoot = json["surveys"];
		const Json::ArrayIndex surveysCount = surveysRoot.size();
		m_surveys.clear();

		const CString INVALID_FILE_FORMAT_ERROR = "저장 된 작업파일을 읽는 도중에 특정 필드 값이 존재하지 않아 정상적으로 로드하지 못 했습니다.";
		for (Json::ArrayIndex i = 0; i < surveysCount; ++i) {
			Survey survey;
			bool result = survey.FromJson(surveysRoot[i]);
			if (!result) {
				Logger::Log(INVALID_FILE_FORMAT_ERROR);
			}
			m_surveys.push_back(survey);
		}

		return TRUE;
	}

	UINT Task::GenerateId() const
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
	Json::Value Parcel2Json(ParcelToStore & parcel)
	{
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

		return parcelRoot;
	}
}