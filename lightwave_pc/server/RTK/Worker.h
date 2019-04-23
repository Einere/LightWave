#pragma once

namespace Workers {
	typedef UINT IdType;

	typedef struct Worker {
		IdType id;
		CString name;
		bool authorized;
	};
}