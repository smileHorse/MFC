
// SieveDlg.h : 头文件
//

#pragma once

#define WM_USER_THREAD_FINISHED WM_USER+0x100

typedef struct tagTHREADPARMS {
	int nMax;
	HWND hWnd;
} THREADPARMS;

// CSieveDlg 对话框
class CSieveDlg : public CDialog
{
// 构造
public:
	CSieveDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SIEVE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnStart();
	afx_msg LONG OnThreadFinished(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};
