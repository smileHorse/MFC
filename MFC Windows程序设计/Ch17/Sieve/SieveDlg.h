
// SieveDlg.h : ͷ�ļ�
//

#pragma once

#define WM_USER_THREAD_FINISHED WM_USER+0x100

typedef struct tagTHREADPARMS {
	int nMax;
	HWND hWnd;
} THREADPARMS;

// CSieveDlg �Ի���
class CSieveDlg : public CDialog
{
// ����
public:
	CSieveDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SIEVE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnStart();
	afx_msg LONG OnThreadFinished(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};
