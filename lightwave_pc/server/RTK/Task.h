#pragma once

#include <map>
#include "json/json.h"
#include "./Shape/DS_Point.h"
#include "./Parcel.h"
#include "File.h"
#include "Survey.h"

namespace SurveyTask {
	typedef std::pair<double, double> Point;
	struct ParcelToStore;

	// 작업에 대한 클래스
	class Task : public File::Storable {
	public:
		Task();

		CString GetTaskName() const;
		void SetTaskName(CString taskName);
		CString GetTaskDesc() const;
		void SetTaskDesc(CString taskDesc);
		CString GetCifPath() const;
		void SetCifPath(CString fileName);
		CString GetLotNumber() const;
		void SetLotNumber(CString lotNumber);
		UINT GetId() const;
		void SetId(UINT id);

		const std::vector<ParcelToStore>& GetParcels() const;
		int AddParcels(const std::vector<DataType::CParcel> pts);
		void ClearParcelPoints();

		BOOL HasStarted() const;
		BOOL Start();
		BOOL Stop();

		void RegisterSurvey(Survey survey);
		Survey* GetSurveyById(UINT id);
		const std::vector<Survey>& GetSurveys() const;
		Survey* GetSurveyByCoord(double x, double y);

		Json::Value toJson();
	public: // Override
		virtual std::string ToFileContent();

	protected:
		virtual BOOL ResolveFileData(const char* data);

		UINT m_id;
		CString m_taskName;
		CString m_taskDesc;
		CString m_cifPath;
		CString m_lotNumber;
		std::vector<ParcelToStore> m_parcels;

		std::vector<SurveyTask::Survey> m_surveys;

		BOOL m_hasStarted = FALSE;
	private:
		UINT GenerateId() const;
	};

	typedef std::pair<double, double> Point;

	struct ParcelToStore {
		CString landNo;
		std::vector<Point> points;
	};

	ParcelToStore Parcel2ParcelToStore(DataType::CParcel& parcel);
	Json::Value Parcel2Json(ParcelToStore& parcel);
}