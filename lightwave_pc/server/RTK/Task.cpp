#include "stdafx.h"
#include "Task.h"

Task::Task(CString title, CString lotNumber, CString desc, CString targetFileName)
{
	m_title = title;
	m_desc = desc;
	m_targetFileName = targetFileName;
	m_lotNumber = lotNumber;
}

Task::~Task()
{
}

void Task::setTitle(const CString title)
{
	m_title = title;
}

void Task::setDesc(const CString desc)
{
	m_desc = desc;
}

void Task::setTargetFileName(const CString fileName)
{
	m_targetFileName = fileName;
}

void Task::setLotNumber(const CString lotNumber)
{
	m_lotNumber = lotNumber;
}

CString Task::getTitle() const
{
	return m_title;
}

CString Task::getDesc() const
{
	return m_desc;
}

CString Task::getTargetFileName() const
{
	return m_targetFileName;
}

CString Task::getLotNumber() const
{
	return m_lotNumber;
}

