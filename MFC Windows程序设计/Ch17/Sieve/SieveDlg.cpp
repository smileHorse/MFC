
// SieveDlg.cpp : 实现文件
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


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CSieveDlg 对话框




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


// CSieveDlg 消息处理程序

BOOL CSieveDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSieveDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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
