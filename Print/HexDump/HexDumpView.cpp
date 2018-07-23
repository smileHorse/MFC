
// HexDumpView.cpp : CHexDumpView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "HexDump.h"
#endif

#include "HexDumpDoc.h"
#include "HexDumpView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define PRINTMARGIN 2

// CHexDumpView

IMPLEMENT_DYNCREATE(CHexDumpView, CScrollView)

BEGIN_MESSAGE_MAP(CHexDumpView, CScrollView)
	ON_WM_CREATE()
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CHexDumpView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CHexDumpView 构造/析构

CHexDumpView::CHexDumpView()
{
	// TODO: 在此处添加构造代码

}

CHexDumpView::~CHexDumpView()
{
}

BOOL CHexDumpView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CScrollView::PreCreateWindow(cs);
}

// CHexDumpView 绘制

void CHexDumpView::OnDraw(CDC* pDC)
{
	CHexDumpDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	if (m_nLinesTotal != 0)
	{
		CRect rect;
		pDC->GetClipBox(&rect);

		UINT nStart = rect.top / m_cyScreen;
		UINT nEnd = min(m_nLinesTotal - 1, (rect.bottom + m_cyScreen - 1) / m_cyScreen);

		CFont* pOldFont = pDC->SelectObject(&m_fontScreen);
		for (UINT i = nStart; i <= nEnd; ++i)
		{
			CString string;
			FormatLine(pDoc, i, string);
			pDC->TextOutW(2, (i * m_cyScreen) + 2, string);
		}
		pDC->SelectObject(pOldFont);
	}
}


void CHexDumpView::FormatLine(CHexDumpDoc* pDoc, UINT nLine, CString& string)
{
	// Get 16 bytes and format them for output
	BYTE b[17];
	::FillMemory(b, 16, 32);
	UINT nCount = pDoc->GetBytes(nLine * 16, 16, b);

	string.Format(_T("%0.8X    %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X "\
		"%0.2X %0.2X- %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X "\
		"%0.2X    "), nLine * 16, 
		b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7], 
		b[8], b[9], b[10], b[11], b[12], b[13], b[14], b[15]);

	// replace non-printable characters with periods
	for (UINT i = 0; i < nCount; i++)
	{
		if (!::IsCharAlphaNumeric(b[i]))
		{
			b[i] = 0x2E;
		}
	}

	// if less than 16 bytes were retrieved, erase to the end of the line.
	b[nCount] = 0;
	string += (char*)b;

	if (nCount < 16)
	{
		UINT pos1 = 59;
		UINT pos2 = 60;
		UINT j = 16 - nCount;
		for (UINT i = 0; i < j; i++)
		{
			string.SetAt(pos1, _T(' '));
			string.SetAt(pos2, _T(' '));
			pos1 -= 3;
			pos2 -= 3;
			if (pos1 == 35)
			{
				string.SetAt(35, _T(' '));
				string.SetAt(36, _T(' '));
				pos1 = 33;
				pos2 = 34;
			}
		}
	}
}

void CHexDumpView::PrintPageHeader(CHexDumpDoc* pDoc, CDC* pDC, UINT nPageNumber)
{
	// formulate the text that appears at the top of page
	CString strHeader = pDoc->GetPathName();
	if (strHeader.GetLength() > 68)
	{
		strHeader = pDoc->GetTitle();
	}

	CString strPageNumber;
	strPageNumber.Format(_T("Page %d"), nPageNumber);

	UINT nSpaces = 81 - strPageNumber.GetLength() - strHeader.GetLength();
	for (UINT i = 0; i < nSpaces; i++)
	{
		strHeader += _T(' ');
	}
	strHeader += strPageNumber;

	// output the text
	UINT y = m_cyPrinter * PRINTMARGIN;
	CFont* pOldFont = pDC->SelectObject(&m_fontPrinter);
	pDC->TextOut(m_cxOffset, y, strHeader);

	// Draw a horizontal line underneath the line of text
	y += (m_cyPrinter * 3) / 2;
	pDC->MoveTo(m_cxOffset, y);
	pDC->LineTo(m_cxOffset + m_cxWidth, y);

	pDC->SelectObject(pOldFont);
}

void CHexDumpView::PrintPage(CHexDumpDoc* pDoc, CDC* pDC, UINT nPageNumber)
{
	if (m_nLinesTotal != 0)
	{
		UINT nStart = (nPageNumber - 1) * m_nLinesPerPage;
		UINT nEnd = min(m_nLinesTotal - 1, nStart + m_nLinesTotal - 1);
		CFont* pOldFont = pDC->SelectObject(&m_fontPrinter);
		for (UINT i = nStart; i <= nEnd; i++)
		{
			CString string;
			FormatLine(pDoc, i, string);
			UINT y = ((i - nStart) + PRINTMARGIN + 3) * m_cyPrinter;
			pDC->TextOut(m_cxOffset, y, string);
		}
		pDC->SelectObject(pOldFont);
	}
}

int CHexDumpView::OnCreate(LPCREATESTRUCT lpcs)
{
	if (CScrollView::OnCreate(lpcs) == -1)
	{
		return -1;
	}

	// create a screen font
	m_fontScreen.CreatePointFont(100, _T("Courier New"));

	// compute the height of one line in the screen font
	CClientDC dc(this);
	TEXTMETRIC tm;
	CFont* pOldFont = dc.SelectObject(&m_fontScreen);
	dc.GetTextMetrics(&tm);
	m_cyScreen = tm.tmHeight + tm.tmExternalLeading;
	dc.SelectObject(pOldFont);
	return 0;
}

// CHexDumpView 打印


void CHexDumpView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

void CHexDumpView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	UINT nDocLength = GetDocument()->GetDocumentLength();
	m_nLinesTotal = (nDocLength + 15) / 16;

	SetScrollSizes(MM_TEXT, CSize(0, m_nLinesTotal * m_cyScreen),
		CSize(0, m_cyScreen * 10), CSize(0, m_cyScreen));
	ScrollToPosition(CPoint(0, 0));
}

BOOL CHexDumpView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CHexDumpView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: 添加额外的打印前进行的初始化过程
	// Create a printer font
	m_fontPrinter.CreatePointFont(100, _T("Courier New"), pDC);

	// compute the width and height of a line in the printer font
	TEXTMETRIC tm;
	CFont* pOldFont = pDC->SelectObject(&m_fontPrinter);
	pDC->GetTextMetrics(&tm);
	m_cyPrinter = tm.tmHeight + tm.tmExternalLeading;
	CSize size = pDC->GetTextExtent(_T("----1----2----"\
		"3----4----5----6----7----8-"), 81);
	pDC->SelectObject(pOldFont);
	m_cxWidth = size.cx;

	// compute the page count
	m_nLinesPerPage = (pDC->GetDeviceCaps(VERTRES) -
		(m_cyPrinter * (3 + (2 * PRINTMARGIN)))) / m_cyPrinter;
	UINT nMaxPage = max(1, (m_nLinesTotal + (m_nLinesPerPage - 1)) / m_nLinesPerPage);
	pInfo->SetMaxPage(nMaxPage);

	// compute the horizonital offset required to center each line of output
	m_cxOffset = (pDC->GetDeviceCaps(HORZRES) - size.cx) / 2;
}

void CHexDumpView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: 添加打印后进行的清理过程
	m_fontPrinter.DeleteObject();
}

void CHexDumpView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	CHexDumpDoc* pDoc = GetDocument();
	PrintPageHeader(pDoc, pDC, pInfo->m_nCurPage);
	PrintPage(pDoc, pDC, pInfo->m_nCurPage);
}

void CHexDumpView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CHexDumpView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CHexDumpView 诊断

#ifdef _DEBUG
void CHexDumpView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CHexDumpView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CHexDumpDoc* CHexDumpView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHexDumpDoc)));
	return (CHexDumpDoc*)m_pDocument;
}
#endif //_DEBUG


// CHexDumpView 消息处理程序
