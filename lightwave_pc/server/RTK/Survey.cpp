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

	void Survey::setWorker(Workers::Worker worker)
	{
		m_worker = worker;
	}

	void Survey::setWorker(UINT id, CString name, CString ip, UINT port)
	{
		m_worker = Workers::Worker(id, name, ip, port);
	}

	SYSTEMTIME Survey::GetUpdatedTime() const
	{
		return m_updatedTime;
	}

	Workers::Worker Survey::GetWorker() const
	{
		return m_worker;
	}

	Json::Value Survey::ToJson() const
	{
		Json::Value root;
		root["updatedTime"] = TimeUtil::convertTime2StrSimple(m_updatedTime).GetString();

		root["worker"] = m_worker.ToJson();

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

	bool Survey::FromJson(Json::Value root)
	{
		Json::Value coordRoot = root["coord"];
		Json::Value memoRoot = root["memo"];
		Json::Value workerRoot = root["worker"];
		Json::Value imgPathsRoot = root["images"];

		if (coordRoot.isNull()
			|| memoRoot.isNull()
			|| workerRoot.isNull()
			|| imgPathsRoot.isNull()) {
			return false;
		}

		bool result = m_worker.FromJson(workerRoot);
		if (!result) {
			return false;
		}

		m_fX = coordRoot["X"].asDouble();
		m_fY = coordRoot["Y"].asDouble();
		
		m_memo = memoRoot.asCString();
		
		m_imagesPaths.clear();
		for (const auto& imgPath : imgPathsRoot) {
			m_imagesPaths.push_back(imgPath.asCString());
		}

		return true;
	}
}