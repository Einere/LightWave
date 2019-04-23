#include "stdafx.h"
#include "Survey.h"
#include "time.h"

namespace SurveyTask {
	Survey::Survey() : Survey(0,0)
	{
		
	}

	Survey::Survey(double fX, double fY) : CDS_Point(fX, fY)
	{
		GetLocalTime(&m_updatedTime);
	}

	Survey::~Survey()
	{
	}

	void Survey::SetMemo(CString memo)
	{
		m_memo = memo;
	}

	CString Survey::GetMemo() const
	{
		return m_memo;
	}

	void Survey::LoadAndGetImages(std::vector<CImage>* out_Images) const
	{
		
		out_Images->clear();

		const int imagesCount = m_imagesPaths.size();
		for (int i = 0; i < imagesCount; ++i) {
			out_Images->push_back(CImage());
			HRESULT hResult = out_Images->at(i).Load(m_imagesPaths[i]);
			if (FAILED(hResult)) {
				CString errorMessage;
				errorMessage.Format("%s 은 정상적인 이미지 파일이 아닙니다.", m_imagesPaths[i]);
				Log::err(errorMessage);
			}
		}
	}

	std::vector<CString> Survey::GetImagesPaths() const
	{
		return m_imagesPaths;
	}

	void Survey::AppendImageFile(CString path)
	{
		m_imagesPaths.push_back(path);
	}

	Json::Value Survey::ToJson() const
	{
		Json::Value root;
		root["updatedTime"] = TimeUtil::convertTime2Str(m_updatedTime).GetString();
		root["coord"] = Json::Value();
		root["coord"]["X"] = m_fX;
		root["coord"]["Y"] = m_fY;

		root["memo"] = m_memo.GetString();
		root["images"] = Json::Value(Json::arrayValue);

		for (const auto& path : m_imagesPaths) {
			root["images"].append(path.GetString());
		}

		return root;
	}

	void Survey::FromJson(Json::Value root)
	{
		Json::Value coord = root["coord"];
		m_fX = coord["X"].asDouble();
		m_fY = coord["Y"].asDouble();

		m_memo = root["memo"].asCString();


		m_imagesPaths.clear();
		for (const auto& imgPath : root["images"]) {
			m_imagesPaths.push_back(imgPath.asCString());
		}
	}
}