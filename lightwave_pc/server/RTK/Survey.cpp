#include "stdafx.h"
#include "Survey.h"
#include "time.h"

namespace SurveyTask {
	Survey::Survey(double fX, double fY, UINT id) : CDS_Point(fX, fY)
	{
		GetLocalTime(&m_updatedTime);
		if (0 == id) m_id = GenerateId();
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

	void Survey::SetName(CString name)
	{
		m_name = name;
	}

	CString Survey::GetName() const
	{
		return m_name;
	}

	void Survey::LoadAndGetImages(std::vector<CImage>* out_Images) const
	{
		out_Images->clear();

		const int imagesCount = m_images.size();
		for (int i = 0; i < imagesCount; ++i) {
			out_Images->push_back(CImage());
			CString imagePath = m_images[i].path;
			HRESULT hResult = out_Images->at(i).Load(imagePath);
			if (FAILED(hResult)) {
				CString errorMessage;
				errorMessage.Format("파일 [%s] 을 열 수 없습니다..", imagePath);
				Logger::Err(errorMessage);
			}
		}
	}

	std::vector<SurveyImage> Survey::GetImages() const
	{
		return m_images;
	}

	void Survey::AppendImage(SurveyImage image)
	{
		m_images.push_back(image);
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

	void Survey::SetSurveyed(bool surveyed)
	{
		m_hasBeenSurveyed = surveyed;
	}

	bool Survey::HasBeenSurveyed() const
	{
		return m_hasBeenSurveyed;
	}

	Json::Value Survey::ToJson() const
	{
		Json::Value root;
		root["id"] = m_id;
		root["hasBeenSurveyed"] = m_hasBeenSurveyed;
		root["updatedTime"] = TimeUtil::ConvertTime2StrSimple(m_updatedTime).GetString();
		root["name"] = m_name.GetString();
		root["worker"] = m_worker.ToJson();

		root["coord"] = Json::Value();
		root["coord"]["X"] = m_fX;
		root["coord"]["Y"] = m_fY;

		root["memo"] = m_memo.GetString();
		root["images"] = Json::Value(Json::arrayValue);

		int imageCount = m_images.size();
		for (int i = 0; i < imageCount; ++i) {
			Json::Value imageRoot;
			imageRoot["path"] = m_images[i].path.GetString();

			Json::Value geoRoot;
			geoRoot["lat"] = m_images[i].geometry.latitude; // 위도
			geoRoot["lon"] = m_images[i].geometry.longitude; // 경도
			geoRoot["azi"] = m_images[i].geometry.azimuth; // 방위
			imageRoot["geometry"] = geoRoot;
			root["images"].append(imageRoot);
		}

		return root;
	}

	bool Survey::FromJson(Json::Value root)
	{
		Json::Value idRoot = root["id"];
		Json::Value hasBeenSurveyedRoot = root["hasBeenSurveyed"];
		Json::Value timeRoot = root["updatedTime"];
		Json::Value nameRoot = root["name"];
		Json::Value coordRoot = root["coord"];
		Json::Value memoRoot = root["memo"];
		Json::Value workerRoot = root["worker"];
		Json::Value imgRoot = root["images"];

		if (idRoot.isNull()
			|| hasBeenSurveyedRoot.isNull()
			|| timeRoot.isNull()
			|| nameRoot.isNull()
			|| coordRoot.isNull()
			|| memoRoot.isNull()
			|| workerRoot.isNull()
			|| imgRoot.isNull()) {
			return false;
		}

		m_id = idRoot.asUInt();
		m_hasBeenSurveyed = hasBeenSurveyedRoot.asBool();
		m_updatedTime = TimeUtil::ConvertStrSimple2Time(timeRoot.asCString());
		m_name = nameRoot.asCString();

		bool result = m_worker.FromJson(workerRoot);
		if (!result) {
			return false;
		}

		m_fX = coordRoot["X"].asDouble();
		m_fY = coordRoot["Y"].asDouble();

		m_memo = memoRoot.asCString();

		m_images.clear();
		for (const auto& imgItem : imgRoot) {
			CString path = imgItem["path"].asCString();
			Geometry geometry = {
				imgItem["geometry"]["lat"].asDouble(),
				imgItem["geometry"]["lon"].asDouble(),
				imgItem["geometry"]["azi"].asDouble()
			};

			m_images.push_back({ path, geometry });
		}

		return true;
	}

	void Survey::Update(const Survey& src)
	{
		m_worker = src.GetWorker();
		m_memo = src.GetMemo();
		m_images = src.GetImages();

		GetLocalTime(&m_updatedTime);
		m_hasBeenSurveyed = true;
	}

	UINT Survey::GenerateId() const
	{
		const int LENGTH = 9;
		SYSTEMTIME curTime;
		GetLocalTime(&curTime);

		CString timeInStr = TimeUtil::ConvertTime2StrNumber(curTime);
		CString idInStr = "1";

		std::srand(time(NULL));
		for (int i = 0; i < LENGTH - 1; ++i) {
			int randomIndex = rand() % LENGTH;
			idInStr += timeInStr[randomIndex];
		}

		return atoi(idInStr);
	}
}