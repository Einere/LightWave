#pragma once

#include <map>
#include "./Shape/DS_Point.h"
#include "./Parcel.h"
#include "File.h"


// 작업에 대한 클래스
class Task : public std::map<CString, CString>, public File::Save {
public:
	Task();
	Task(const Task& other);
	const std::vector< std::reference_wrapper<DataType::CParcel>>& getParcels() const;

	void clearParcelPoints();
	//int addParcels(const DataType::CParcel* pts, size_t offset, size_t count);
	int addParcels(std::vector<std::reference_wrapper<DataType::CParcel>> pts);
	//void addParcelPoint(const CDS_Point pt);

public: // Override
	virtual CString toFileContent();

protected:
	virtual CString getDefaultPath();

private:
	std::vector< std::reference_wrapper<DataType::CParcel>> m_parcels;
};