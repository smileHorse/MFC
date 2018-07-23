
// MdiSquaresView.cpp : CMdiSquaresView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MdiSquares.h"
#endif

#include "MdiSquaresDoc.h"
#include "MdiSquaresView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMdiSquaresView

IMPLEMENT_DYNCREATE(CMdiSquaresView, CView)

BEGIN_MESSAGE_MAP(CMdiSquaresView, CView)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CMdiSquaresView 构造/析构

CMdiSquaresView::CMdiSquaresView()
{
	// TODO: 在此处添加构造代码

}

CMdiSquaresView::~CMdiSquaresView()
{
}

BOOL CMdiSquaresView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMdiSquaresView 绘制

void CMdiSquaresView::OnDraw(CDC* pDC)
{
	CMdiSquaresDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	// Set the mapping mode to MM_LOENGLISH
	pDC->SetMapMode(MM_LOENGLISH);

	// Draw the 16 squares
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			COLORREF color = pDoc->GetSquare(i, j);
			CBrush brush(color);
			int x1 = (j * 70) + 35;
			int y1 = (i * -70) - 35;
			int x2 = x1 + 70;
			int y2 = y1 - 70;
			CRect rect(x1, y1, x2, y2);
			pDC->FillRect(rect, &brush);
		}
	}

	// Then draw the grid lines surrounding them
	for (int x = 35; x <= 315; x += 70)
	{
		pDC->MoveTo(x, -35);
		pDC->LineTo(x, -315);
	}
	for (int y = -35; y >= -315; y -= 70)
	{
		pDC->MoveTo(35, y);
		pDC->LineTo(315, y);
	}
}


// CMdiSquaresView 诊断

#ifdef _DEBUG
void CMdiSquaresView::AssertValid() const
{
	CView::AssertValid();
}

void CMdiSquaresView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

void CMdiSquaresView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CView::OnLButtonDown(nFlags, point);

	// Convert click coordinates to MM_LOENGLISH units
	CClientDC dc(this);
	dc.SetMapMode(MM_LOENGLISH);
	CPoint pos = point;
	dc.DPtoLP(&pos);

	// If a square was clicked, set its color to the current color
	if (pos.x >= 35 && pos.x <= 315 && pos.y <= -35 && pos.y >= -315)
	{
		int i = (-pos.y - 35) / 70;
		int j = (pos.x - 35) / 70;
		CMdiSquaresDoc* pDoc = GetDocument();
		COLORREF clrCurrentColor = pDoc->GetCurrentColor();
		pDoc->SetSquare(i, j, clrCurrentColor);
	}
}

CMdiSquaresDoc* CMdiSquaresView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMdiSquaresDoc)));
	return (CMdiSquaresDoc*)m_pDocument;
}
#endif //_DEBUG


// CMdiSquaresView 消息处理程序
