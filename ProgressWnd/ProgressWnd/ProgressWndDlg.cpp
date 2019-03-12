
// ProgressWndDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ProgressWnd.h"
#include "ProgressWndDlg.h"
#include "afxdialogex.h"

#include "MessageDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CProgressWndDlg �Ի���




CProgressWndDlg::CProgressWndDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProgressWndDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProgressWndDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS, m_progressCtrl);
	DDX_Control(pDX, IDC_STATIC_PROGRESS, m_progressStatic);
}

BEGIN_MESSAGE_MAP(CProgressWndDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START_PROGRESS, &CProgressWndDlg::OnBnClickedButtonStartProgress)
	ON_MESSAGE(PROGRESS_OFFSET, &CProgressWndDlg::onProgressOffset)
	ON_MESSAGE(PROGRESS_FINISHED, &CProgressWndDlg::onProgressFinished)
END_MESSAGE_MAP()


// CProgressWndDlg ��Ϣ�������

BOOL CProgressWndDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_progressCtrl.SendMessage(PBM_SETBARCOLOR, 0, (LPARAM)RGB(255, 0, 0));
	m_progressCtrl.SendMessage(PBM_SETBKCOLOR, 0, (LPARAM)RGB(0, 255, 0));
	m_progressCtrl.ShowWindow(SW_HIDE);
	m_progressStatic.ShowWindow(SW_HIDE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CProgressWndDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CProgressWndDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CProgressWndDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CProgressWndDlg::OnBnClickedButtonStartProgress()
{
	m_progressCtrl.ShowWindow(SW_SHOW);
	m_progressStatic.ShowWindow(SW_SHOW);

	m_progressCtrl.SetRange(0, 100);
	m_progressCtrl.SetPos(0);

	m_progressThread.setWnd(this);
	m_progressThread.startProgress();
	m_workingThread.setWnd(this);
	m_workingThread.startWorking();
}

LRESULT CProgressWndDlg::onProgressOffset(WPARAM wParam, LPARAM lParam)
{
	int pos = m_progressCtrl.GetPos();
	if (pos == 100)
	{
		m_progressCtrl.SetPos(0);
	}
	m_progressCtrl.OffsetPos(1);

	return 0;
}

LRESULT CProgressWndDlg::onProgressFinished(WPARAM wParam, LPARAM lParam)
{
	m_progressThread.setStop(TRUE);

	m_progressCtrl.SetPos(0);
	m_progressStatic.SetWindowText(_T(""));
	m_progressCtrl.ShowWindow(SW_HIDE);
	m_progressStatic.ShowWindow(SW_HIDE);

	return 0;
}
