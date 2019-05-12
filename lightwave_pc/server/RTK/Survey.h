#pragma once

#include "./Shape/DS_Point.h"
#include "json.h"
#include "Worker.h"

namespace SurveyTask {
	struct Geometry {
		double latitude;
		double longitude;
		double azimuth;
	};

	struct SurveyImage {
		CString path;
		Geometry geometry;
	};

	class Survey
		: public DataType::ShapeType::CDS_Point
	{
	public:
		Survey(double fX = 0.0, double fY = 0.0, UINT id = 0);
		Survey(const Json::Value& root);
		//Survey(const Survey& Source);
		~Survey();

		UINT GetId() const;

		void SetMemo(CString memo);
		CString GetMemo() const;

		void SetName(CString name);
		CString GetName() const;

		void LoadAndGetImages(std::vector<CImage>* out_Images) const;
		std::vector<SurveyImage> GetImages() const;
		void AppendImage(SurveyImage image);

		void setWorker(Workers::Worker worker);
		void setWorker(UINT id, CString name, CString ip, UINT port);

		SYSTEMTIME GetUpdatedTime() const;

		Workers::Worker GetWorker() const;

		void SetSurveyed(bool surveyed = TRUE);
		bool HasBeenSurveyed() const;

		Json::Value ToJson() const;
		bool FromJson(Json::Value root);

		void Update(const Survey& src);

	private:
		UINT m_id;
		CString m_name;
		SYSTEMTIME m_updatedTime;
		Workers::Worker m_worker;
		CString m_memo;
		std::vector<SurveyImage> m_images;
		//std::vector<CString> m_imagesPaths;
		//std::vector<Geometry> m_geometries;

		BOOL m_hasBeenSurveyed = FALSE;

		UINT GenerateId() const;
	};
}