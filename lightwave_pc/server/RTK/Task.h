#pragma once
class Task
{
public:
	Task(CString title="no title", CString lotNumber="-1", CString desc="no desc", CString targetFileName=NULL);
	~Task();

	void setTitle(const CString title);
	void setDesc(const CString desc);
	void setTargetFileName(const CString fileName);
	void setLotNumber(const CString lotNumber);

	CString getTitle() const;
	CString getDesc() const;
	CString getTargetFileName() const;
	CString getLotNumber() const;

protected:
	CString m_title;
	CString m_desc;
	CString m_targetFileName;
	CString m_lotNumber;
};
