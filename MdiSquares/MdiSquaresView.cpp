
// MdiSquaresView.cpp : CMdiSquaresView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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

// CMdiSquaresView ����/����

CMdiSquaresView::CMdiSquaresView()
{
	// TODO: �ڴ˴���ӹ������

}

CMdiSquaresView::~CMdiSquaresView()
{
}

BOOL CMdiSquaresView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMdiSquaresView ����

void CMdiSquaresView::OnDraw(CDC* pDC)
{
	CMdiSquaresDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
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


// CMdiSquaresView ���

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

CMdiSquaresDoc* CMdiSquaresView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMdiSquaresDoc)));
	return (CMdiSquaresDoc*)m_pDocument;
}
#endif //_DEBUG


// CMdiSquaresView ��Ϣ�������
