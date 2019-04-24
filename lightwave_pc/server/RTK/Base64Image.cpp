#include "stdafx.h"
#include "Base64Image.h"

namespace SurveyTask {

	Base64Image::Base64Image(CString parentDir, CString encodedString)
		: File::Storable(parentDir), m_encoded(encodedString)
	{
		std::srand((UINT)time(NULL));
		CString fileName;
		m_fileName.Format("SampleImage%d", std::rand());

		m_ext = "jpg";
		m_parentPath = parentDir + "/images";
	}

	Base64Image::~Base64Image()
	{
	}

	BOOL Base64Image::resolveFileData(const char * data)
	{
		return TRUE;
	}

	std::string Base64Image::toFileContent()
	{
		if ("" == m_decoded) {
			m_decoded = base64_decode(m_encoded.GetString());
		}

		return m_decoded;

		/*const unsigned char* img = reinterpret_cast<const unsigned char*>(decoded.c_str());
		pTask->saveImage(img, decoded.length(), "test.jpg");

		const BOOL result = CreateDir(imageDir);

		CString path;
		CString dirPath = Path::getDirPath(m_filePath);
		path.Format("%s/images/%s", dirPath, fileName);

		CFile file;
		const bool isOpenSucceed = file.Open(path, CFile::modeWrite | CFile::modeCreate);
		assert(isOpenSucceed);

		file.Write((void*)img, size);
		file.Close();

		return TRUE;*/
	}
}