#pragma once

#include <map>
#include "./Shape/DS_Point.h"
#include "./Parcel.h"
#include "File.h"


// 작업에 대한 클래스
class Task : public File::Save {
public:
	Task();

	CString getTaskName() const;
	void setTaskName(CString taskName);
	CString getTaskDesc() const;
	void setTaskDesc(CString taskDesc);
	CString getFileName() const;
	void setFileName(CString fileName);
	CString getLotNumber() const;
	void setLotNumber(CString lotNumber);
	UINT getId() const;
	void setId(UINT id);

	const std::vector< std::reference_wrapper<DataType::CParcel>>& getParcels() const;
	int addParcels(std::vector<std::reference_wrapper<DataType::CParcel>> pts);

	void clearParcelPoints();

public: // Override
	virtual CString toFileContent();

protected:
	virtual CString getDefaultPath();
	virtual BOOL resolveFileData(const char* data);

	UINT m_id;
	CString m_taskName;
	CString m_taskDesc;
	CString m_fileName;
	CString m_lotNumber;
	std::vector< std::reference_wrapper<DataType::CParcel>> m_parcels;

private:
	UINT generateId() const;
};