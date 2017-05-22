
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once

#include "SpecialStatusBar.h"

class CMainFrame : public CFrameWnd
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CSpecialStatusBar        m_wndStatusBar;

// ���ɵ���Ϣӳ�亯��
protected:
	int m_nPercentDone;

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);

	afx_msg LRESULT OnUpdateImageStats(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnThreadUpdate(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnThreadFinished(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnThreadAborted(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

};


