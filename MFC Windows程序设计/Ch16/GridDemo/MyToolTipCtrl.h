#pragma once

class CMyToolTipCtrl : public CToolTipCtrl
{
public:
	CMyToolTipCtrl();

public:
	BOOL AddRectTool(CWnd* pWnd, LPCTSTR pszText, LPCRECT pRect, UINT nIDTool);
	BOOL AddWindowTool(CWnd* pWnd, LPCTSTR pszText);
	virtual ~CMyToolTipCtrl();

protected:
	DECLARE_MESSAGE_MAP()
};