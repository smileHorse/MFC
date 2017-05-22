
// SieveDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Sieve.h"
#include "SieveDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

UINT ThreadProc(LPVOID pParam);
int Sieve(int nMax);


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


// CSieveDlg �Ի���




CSieveDlg::CSieveDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSieveDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSieveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSieveDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_MESSAGE(WM_USER_THREAD_FINISHED, OnThreadFinished)
END_MESSAGE_MAP()


// CSieveDlg ��Ϣ�������

BOOL CSieveDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSieveDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSieveDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSieveDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSieveDlg::OnStart()
{
	int nMax = GetDlgItemInt(IDC_MAX);
	if (nMax < 10)
	{
		MessageBox(_T("The number you enter must be 10 or higher"));
		GetDlgItem(IDC_MAX)->SetFocus();
		return;
	}

	SetDlgItemText(IDC_RESULT, _T(""));
	GetDlgItem(IDC_START)->EnableWindow(FALSE);

	THREADPARMS* ptp = new THREADPARMS;
	ptp->nMax = nMax;
	ptp->hWnd = m_hWnd;
	AfxBeginThread(ThreadProc, ptp);
}

LONG CSieveDlg::OnThreadFinished( WPARAM wParam, LPARAM lParam )
{
	SetDlgItemInt(IDC_RESULT, (int)wParam);
	GetDlgItem(IDC_START)->EnableWindow(TRUE);
	return 0;
}

UINT ThreadProc(LPVOID pParam)
{
	THREADPARMS* ptp = (THREADPARMS*)pParam;
	int nMax = ptp->nMax;
	HWND hWnd = ptp->hWnd;
	delete ptp;

	int nCount = Sieve(nMax);
	::PostMessage(hWnd, WM_USER_THREAD_FINISHED, (WPARAM)nCount, 0);
	return 0;
}

int Sieve(int nMax)
{
	PBYTE pBuffer = new BYTE[nMax + 1];
	::FillMemory(pBuffer, nMax + 1, 1);

	int nLimit = 2;
	while(nLimit * nLimit < nMax)
		nLimit++;

	for (int i = 2; i <= nLimit; i++)
	{
		if (pBuffer[i])
		{
			for (int k = i + 1; k <= nMax; k += i)
			{
				pBuffer[k] = 0;
			}
		}
	}

	int nCount = 0;
	for (int i = 2; i <= nMax; i++)
	{
		if (pBuffer[i])
		{
			nCount++;
		}
	}

	delete[] pBuffer;
	return nCount;
}
