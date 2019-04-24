#pragma once

#include "./Shape/DS_Point.h"
#include "json.h"
#include "Worker.h"

namespace SurveyTask {
	class Survey 
		: public DataType::ShapeType::CDS_Point
	{
	public:
		Survey();
		Survey(double fX, double fY);
		//Survey(const Survey& Source);
		~Survey();

		void SetMemo(CString memo);
		CString GetMemo() const;

		void LoadAndGetImages(std::vector<CImage>* out_Images) const;
		std::vector<CString> GetImagesPaths() const;
		void AppendImageFile(CString path);

		void setWorker(Workers::Worker worker);
		void setWorker(UINT id, CString name, CString ip, UINT port);

		SYSTEMTIME GetUpdatedTime() const;

		Workers::Worker GetWorker() const;

		Json::Value ToJson() const;
		bool FromJson(Json::Value root);
	private:
		SYSTEMTIME m_updatedTime;
		Workers::Worker m_worker;
		CString m_memo;
		std::vector<CString> m_imagesPaths;
	};
}