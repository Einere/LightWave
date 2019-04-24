#pragma once

#include "ConnectionStateDlg.h"

class StatePane : public CDockablePane
{
public:
	StatePane();
	~StatePane();


	void update();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT onUpdate(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

private:
	ConnectionStateDlg* m_stateDlg;
};