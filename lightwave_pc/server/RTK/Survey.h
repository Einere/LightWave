#pragma once

#include "./Shape/DS_Point.h"
#include "json.h"

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

		Json::Value ToJson() const;
		void FromJson(Json::Value root);
	private:
		SYSTEMTIME m_updatedTime;
		CString m_memo;
		std::vector<CString> m_imagesPaths;
	};
}