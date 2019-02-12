#pragma once

#include "ConnectionStateDlg.h"

class StatePane : public CDockablePane
{
public:
	StatePane();
	~StatePane();

	void update(bool isListening, const std::vector<std::shared_ptr<SocketWorker>> workers);

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()

private:
	ConnectionStateDlg m_stateDlg;
};