
// ProgressWndDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"

#include "Thread/ProgressThread.h"
#include "Thread/WorkingThread.h"


// CProgressWndDlg �Ի���
class CProgressWndDlg : public CDialogEx
{
// ����
public:
	CProgressWndDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PROGRESSWND_DIALOG };

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
	afx_msg void OnBnClickedButtonStartProgress();
	afx_msg LRESULT onProgressOffset(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT onProgressFinished(WPARAM wParam, LPARAM lParam);
	
	DECLARE_MESSAGE_MAP()

public:
	CProgressCtrl m_progressCtrl;
	CStatic m_progressStatic;

	CProgressThread m_progressThread;
	CWorkingThread m_workingThread;
};
