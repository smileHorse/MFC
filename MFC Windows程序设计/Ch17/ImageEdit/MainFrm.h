
// MainFrm.h : CMainFrame 类的接口
//

#pragma once

#include "SpecialStatusBar.h"

class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CSpecialStatusBar        m_wndStatusBar;

// 生成的消息映射函数
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


