#pragma once

#include <map>
#include "json/json.h"
#include "./Shape/DS_Point.h"
#include "./Parcel.h"
#include "File.h"

namespace SurveyTask {
	typedef std::pair<double, double> Point;
	struct ParcelToStore;

	// �۾��� ���� Ŭ����
	class Task : public File::Save {
	public:
		Task();

		CString getTaskName() const;
		void setTaskName(CString taskName);
		CString getTaskDesc() const;
		void setTaskDesc(CString taskDesc);
		CString getFileName() const;
		void setFileName(CString fileName);
		CString getLotNumber() const;
		void setLotNumber(CString lotNumber);
		UINT getId() const;
		void setId(UINT id);

		const std::vector<ParcelToStore>& getParcels() const;
		int addParcels(const std::vector<DataType::CParcel> pts);
		void clearParcelPoints();

		BOOL saveImage(const CString byteInStr, const CString fileName);

		BOOL hasStarted() const;
		BOOL start();
		BOOL stop();

		Json::Value toJson();
	public: // Override
		virtual CString toFileContent();

	protected:
		virtual CString getDefaultPath();
		virtual BOOL resolveFileData(const char* data);

		UINT m_id;
		CString m_taskName;
		CString m_taskDesc;
		CString m_fileName;
		CString m_lotNumber;
		std::vector<ParcelToStore> m_parcels;

		BOOL m_hasStarted = FALSE;
	private:
		UINT generateId() const;
	};

	typedef std::pair<double, double> Point;

	struct ParcelToStore {
		CString landNo;
		std::vector<Point> points;
	};

	ParcelToStore Parcel2ParcelToStore(DataType::CParcel& parcel);
}