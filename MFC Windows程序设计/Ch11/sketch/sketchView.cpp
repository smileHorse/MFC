
// sketchView.cpp : CsketchView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "sketch.h"
#endif

#include "sketchDoc.h"
#include "sketchView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "Line.h"


// CsketchView

IMPLEMENT_DYNCREATE(CsketchView, CScrollView)

BEGIN_MESSAGE_MAP(CsketchView, CScrollView)
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CsketchView ����/����

CsketchView::CsketchView()
{
	// TODO: �ڴ˴���ӹ������
	m_hCursor = AfxGetApp()->LoadStandardCursor(IDC_CROSS);
}

CsketchView::~CsketchView()
{
}

BOOL CsketchView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CScrollView::PreCreateWindow(cs);
}

// CsketchView ����

void CsketchView::OnDraw(CDC* pDC)
{
	CsketchDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	// Draw the snap grid
	if (pDoc->IsGridVisible())
	{
		for (int x = 25; x < 1600; x += 25)
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
		for (int i = 0; i < nCount; ++i)
		{
			pDoc->GetLine(i)->Draw(pDC);
		}
	}
}


// CsketchView ���

#ifdef _DEBUG
void CsketchView::AssertValid() const
{
	CView::AssertValid();
}

void CsketchView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CsketchDoc* CsketchView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CsketchDoc)));
	return (CsketchDoc*)m_pDocument;
}


#endif //_DEBUG


// CsketchView ��Ϣ�������

void CsketchView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	SetScrollSizes(MM_LOENGLISH, CSize(1600, 1200));
}

void CsketchView::OnUpdate( CView* pSender, LPARAM lHint, CObject* pHint )
{
	if (lHint == 0x7c)
	{
		CLine* pLine = (CLine*)pHint;
		ASSERT(pLine->IsKindOf(RUNTIME_CLASS(CLine)));
		CClientDC dc(this);
		OnPrepareDC(&dc);
		pLine->Draw(&dc);
		return;
	}
	CScrollView::OnUpdate(pSender, lHint, pHint);
}

BOOL CsketchView::OnSetCursor( CWnd* pWnd, UINT nHitTest, UINT message )
{
	::SetCursor(m_hCursor);
	return TRUE;
}

void CsketchView::OnLButtonDown( UINT nFlags, CPoint point )
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

void CsketchView::OnMouseMove( UINT nFlags, CPoint point )
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

void CsketchView::OnLButtonUp( UINT nFlags, CPoint point )
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

		CsketchDoc* pDoc = GetDocument();
		CLine* pLine = pDoc->AddLine(m_ptFrom, m_ptTo);
	}
}

void CsketchView::InvertLine( CDC* pDC, POINT from, POINT to )
{
	int nOldMode = pDC->SetROP2(R2_NOT);
	pDC->MoveTo(from);
	pDC->LineTo(to);
	pDC->SetROP2(nOldMode);
}
