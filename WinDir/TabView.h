#pragma once

#include "stdafx.h"

class CTabView : public CCtrlView
{
	DECLARE_DYNCREATE(CTabView)

public:
	CTabView() :
		CCtrlView(_T("SysTabControl32"), AFX_WS_DEFAULT_VIEW)
	{}
	
	CTabCtrl& GetTabCtrl() const {
		return *(CTabCtrl*)this;
	}
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
};
