#pragma once

#include "MyToolTipCtrl.h"

class CSettingDialog : public CDialog
{
public: 
	int m_nWeight;
	CSettingDialog(CWnd* parent = NULL);

	enum { IDD = IDD_SETTINGDLG };
	CSpinButtonCtrl m_wndSpinVert;
	CSpinButtonCtrl m_wndSpinHorz;
	CSliderCtrl m_wndSlider;
	int m_cx;
	int m_cy;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	CMyToolTipCtrl m_ctlTT;

	virtual BOOL OnInitDialog();
	virtual void OnOk();

	DECLARE_MESSAGE_MAP()
};