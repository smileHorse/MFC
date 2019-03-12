
// ProgressWndDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ProgressWnd.h"
#include "ProgressWndDlg.h"
#include "afxdialogex.h"

#include "MessageDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CProgressWndDlg 对话框




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


// CProgressWndDlg 消息处理程序

BOOL CProgressWndDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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
	m_progressCtrl.SendMessage(PBM_SETBARCOLOR, 0, (LPARAM)RGB(255, 0, 0));
	m_progressCtrl.SendMessage(PBM_SETBKCOLOR, 0, (LPARAM)RGB(0, 255, 0));
	m_progressCtrl.ShowWindow(SW_HIDE);
	m_progressStatic.ShowWindow(SW_HIDE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CProgressWndDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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
