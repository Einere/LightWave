#pragma once

#include "File.h"
#include "base64.h"

namespace SurveyTask {
	class Base64Image
		: public File::Storable
	{
	public:
		Base64Image(CString parentDir=File::rootDir, CString encodedString = "");
		~Base64Image();

	protected:
		virtual BOOL ResolveFileData(const char* data);
		virtual std::string ToFileContent();

		const CString m_encoded = "";
		std::string m_decoded = "";
	};
}