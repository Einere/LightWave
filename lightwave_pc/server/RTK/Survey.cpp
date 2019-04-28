#include "stdafx.h"
#include "Survey.h"
#include "time.h"

namespace SurveyTask {
	Survey::Survey(double fX, double fY, UINT id) : CDS_Point(fX, fY)
	{
		GetLocalTime(&m_updatedTime);
		if(0==id) m_id = GenerateId();
	}

	Survey::Survey(const Json::Value& root)
	{
		FromJson(root);
	}

	Survey::~Survey()
	{
	}

	UINT Survey::GetId() const
	{
		return m_id;
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
				errorMessage.Format("%s �� �������� �̹��� ������ �ƴմϴ�.", m_imagesPaths[i]);
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

	void Survey::SetSurveyed(BOOL surveyed)
	{
		m_hasBeenSurveyed = surveyed;
	}

	BOOL Survey::HasBeenSurveyed() const
	{
		return m_hasBeenSurveyed;
	}

	Json::Value Survey::ToJson() const
	{
		Json::Value root;
		root["id"] = m_id;
		root["hasBeenSurveyed"] = m_hasBeenSurveyed;
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
		Json::Value idRoot = root["id"];
		Json::Value hasBeenSurveyedRoot = root["hasBeenSurveyed"];
		Json::Value timeRoot = root["updatedTime"];
		Json::Value coordRoot = root["coord"];
		Json::Value memoRoot = root["memo"];
		Json::Value workerRoot = root["worker"];
		Json::Value imgPathsRoot = root["images"];

		if (idRoot.isNull()
			|| hasBeenSurveyedRoot.isNull()
			|| timeRoot.isNull()
			|| coordRoot.isNull()
			|| memoRoot.isNull()
			|| workerRoot.isNull()
			|| imgPathsRoot.isNull()) {
			return false;
		}

		m_id = idRoot.asUInt();
		m_hasBeenSurveyed = hasBeenSurveyedRoot.asBool();
		m_updatedTime = TimeUtil::convertStrSimple2Time(timeRoot.asCString());

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

	void Survey::Update(const Survey& src)
	{
		m_worker = src.GetWorker();
		m_memo = src.GetMemo();
		m_imagesPaths = src.GetImagesPaths();

		GetLocalTime(&m_updatedTime);
		m_hasBeenSurveyed = true;
	}

	UINT Survey::GenerateId() const
	{
		const int LENGTH = 9;
		SYSTEMTIME curTime;
		GetLocalTime(&curTime);

		CString timeInStr = TimeUtil::convertTime2StrNumber(curTime);
		CString idInStr = "1";

		std::srand(time(NULL));
		for (int i = 0; i < LENGTH-1; ++i) {
			int randomIndex = rand() % LENGTH;
			idInStr+=timeInStr[randomIndex];
		}

		return atoi(idInStr);
	}
}