
// SketchView.cpp : CSketchView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Sketch.h"
#endif

#include "Line.h"
#include "SketchDoc.h"
#include "SketchView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSketchView

IMPLEMENT_DYNCREATE(CSketchView, CScrollView)

BEGIN_MESSAGE_MAP(CSketchView, CScrollView)
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CSketchView ����/����

CSketchView::CSketchView()
{
	// TODO: �ڴ˴���ӹ������
	m_hCursor = AfxGetApp()->LoadStandardCursor(IDC_CROSS);
}

CSketchView::~CSketchView()
{
}

BOOL CSketchView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CScrollView::PreCreateWindow(cs);
}

void CSketchView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	SetScrollSizes(MM_LOENGLISH, CSize(1600, 1200));
}

void CSketchView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	if (lHint = 0x7C)
	{
		CLine* pLine = (CLine*)pHint;
		if (pLine != NULL)
		{
			ASSERT(pLine->IsKindOf(RUNTIME_CLASS(CLine)));
			CClientDC dc(this);
			OnPrepareDC(&dc);
			pLine->Draw(&dc);
			return;
		}
	}
	CScrollView::OnUpdate(pSender, lHint, pHint);
}

// CSketchView ����

void CSketchView::OnDraw(CDC* pDC)
{
	CSketchDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	// Draw the snap grid
	if (pDoc->IsGridVisible())
	{
		for (int  x = 25; x < 1600; x += 25)
		{
			for (int y = -25; y > -1200; y -= 25)
			{
				pDC->SetPixel(x, y, RGB(128, 128, 128));
			}
		}
	}

	// Draw the lines
	int nCount = pDoc->GetLineCount();
	if (nCount)
	{
		for (int i = 0; i < nCount; i++)
		{
			pDoc->GetLine(i)->Draw(pDC);
		}
	}
}


// CSketchView ���

#ifdef _DEBUG
void CSketchView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CSketchView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

void CSketchView::InvertLine(CDC* pDC, POINT from, POINT to)
{
	int nOldMode = pDC->SetROP2(R2_NOT);
	pDC->MoveTo(from);
	pDC->LineTo(to);
	pDC->SetROP2(nOldMode);
}

BOOL CSketchView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	::SetCursor(m_hCursor);
	return TRUE;
}

void CSketchView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CScrollView::OnLButtonDown(nFlags, point);

	CPoint pos = point;
	CClientDC dc(this);
	OnPrepareDC(&dc);
	dc.DPtoLP(&pos);

	if (GetDocument()->IsGridVisible())
	{
		pos.x = ((pos.x + 12) / 25) * 25;
		pos.y = ((pos.y - 12) / 25) * 25;
	}

	m_ptFrom = pos;
	m_ptTo = pos;
	SetCapture();
}

void CSketchView::OnMouseMove(UINT nFlags, CPoint point)
{
	CScrollView::OnMouseMove(nFlags, point);
	if (GetCapture() == this)
	{
		CPoint pos = point;
		CClientDC dc(this);
		OnPrepareDC(&dc);
		dc.DPtoLP(&pos);

		if (GetDocument()->IsGridVisible())
		{
			pos.x = ((pos.x + 12) / 25) * 25;
			pos.y = ((pos.y - 12) / 25) * 25;
		}

		if (m_ptTo != pos)
		{
			InvertLine(&dc, m_ptFrom, m_ptTo);
			InvertLine(&dc, m_ptFrom, pos);
			m_ptTo = pos;
		}
	}
}

void CSketchView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CScrollView::OnLButtonUp(nFlags, point);

	if (GetCapture() == this)
	{
		::ReleaseCapture();

		CPoint pos = point;
		CClientDC dc(this);
		OnPrepareDC(&dc);
		dc.DPtoLP(&pos);

		if (GetDocument()->IsGridVisible())
		{
			pos.x = ((pos.x + 12) / 25) * 25;
			pos.y = ((pos.y - 12) / 25) * 25;
		}

		InvertLine(&dc, m_ptFrom, m_ptTo);
		CSketchDoc* pDoc = GetDocument();
		CLine* pLine = pDoc->AddLine(m_ptFrom, m_ptTo);
	}
}

CSketchDoc* CSketchView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSketchDoc)));
	return (CSketchDoc*)m_pDocument;
}
#endif //_DEBUG


// CSketchView ��Ϣ�������
