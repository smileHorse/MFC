
// ImageEditView.cpp : CImageEditView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "ImageEdit.h"
#endif

#include "ImageEditDoc.h"
#include "ImageEditView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageEditView

IMPLEMENT_DYNCREATE(CImageEditView, CScrollView)

BEGIN_MESSAGE_MAP(CImageEditView, CScrollView)
END_MESSAGE_MAP()

// CImageEditView 构造/析构

CImageEditView::CImageEditView()
{
	// TODO: 在此处添加构造代码

}

CImageEditView::~CImageEditView()
{
}

BOOL CImageEditView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CScrollView::PreCreateWindow(cs);
}

// CImageEditView 绘制

void CImageEditView::OnDraw(CDC* pDC)
{
	CImageEditDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CBitmap* pBitmap = pDoc->GetBitmap();

	if (pBitmap != NULL)
	{
		CPalette* pOldPalette;
		CPalette* pPalette = pDoc->GetPalette();

		if (pPalette != NULL)
		{
			pOldPalette = pDC->SelectPalette(pPalette, FALSE);
			pDC->RealizePalette();
		}

		DIBSECTION ds;
		pBitmap->GetObject(sizeof(DIBSECTION), &ds);

		CDC memDC;
		memDC.CreateCompatibleDC(pDC);
		CBitmap* pOldBitmap = memDC.SelectObject(pBitmap);

		pDC->BitBlt(0, 0, ds.dsBm.bmWidth, ds.dsBm.bmHeight, &memDC, 0, 0, SRCCOPY);

		memDC.SelectObject(pOldBitmap);

		if (pPalette != NULL)
		{
			pDC->SelectPalette(pOldPalette, FALSE);
		}
	}
}

void CImageEditView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CString string;
	CSize sizeTotal;
	CBitmap* pBitmap = GetDocument()->GetBitmap();

	// if a bitmap is loaded, set the view size equal to the bitmap size.
	// otherwise, set the view's width and height to 0
	if (pBitmap != NULL)
	{
		DIBSECTION ds;
		pBitmap->GetObject(sizeof(DIBSECTION), &ds);
		sizeTotal.cx = ds.dsBm.bmWidth;
		sizeTotal.cy = ds.dsBm.bmHeight;
		string.Format(_T("\t%d x %d, %d bpp"), ds.dsBm.bmWidth, ds.dsBm.bmHeight, ds.dsBmih.biBitCount);
	}
	else
	{
		sizeTotal.cx = sizeTotal.cy = 0;
		string.Empty();
	}

	AfxGetMainWnd()->SendMessage(WM_USER_UPDATE_STATS, 0, (LPARAM)(LPCTSTR)string);
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CImageEditView 诊断

#ifdef _DEBUG
void CImageEditView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImageEditView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImageEditDoc* CImageEditView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageEditDoc)));
	return (CImageEditDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageEditView 消息处理程序
