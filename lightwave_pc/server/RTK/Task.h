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

		CString getTaskName() const;
		void setTaskName(CString taskName);
		CString getTaskDesc() const;
		void setTaskDesc(CString taskDesc);
		CString getCifPath() const;
		void setCifPath(CString fileName);
		CString getLotNumber() const;
		void setLotNumber(CString lotNumber);
		UINT getId() const;
		void setId(UINT id);

		const std::vector<ParcelToStore>& getParcels() const;
		int addParcels(const std::vector<DataType::CParcel> pts);
		void clearParcelPoints();

		BOOL hasStarted() const;
		BOOL start();
		BOOL stop();

		void registerSurvey(Survey survey);
		Survey* GetSurveyById(UINT id);
		const std::vector<Survey>& getSurveys() const;
		Survey* GetSurveyByCoord(double x, double y);

		Json::Value toJson();
	public: // Override
		virtual std::string toFileContent();

	protected:
		virtual BOOL resolveFileData(const char* data);

		UINT m_id;
		CString m_taskName;
		CString m_taskDesc;
		CString m_cifPath;
		CString m_lotNumber;
		std::vector<ParcelToStore> m_parcels;

		std::vector<SurveyTask::Survey> m_surveys;

		BOOL m_hasStarted = FALSE;
	private:
		UINT generateId() const;
	};

	typedef std::pair<double, double> Point;

	struct ParcelToStore {
		CString landNo;
		std::vector<Point> points;
	};

	ParcelToStore parcel2ParcelToStore(DataType::CParcel& parcel);
	Json::Value parcel2Json(ParcelToStore& parcel);
}