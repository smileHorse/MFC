#pragma once

#include <Windows.h>

class CSpecialStatusBar : public CStatusBar
{
public:
	void SetProgress(int nPercent);
	void SetImageStats(LPCTSTR pszStats);
	CSpecialStatusBar();
	virtual ~CSpecialStatusBar();

protected:
	CProgressCtrl m_wndProgress;
	afx_msg int OnCreate(LPCREATESTRUCT lpcs);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
};