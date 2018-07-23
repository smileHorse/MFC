
// GDIView.cpp : CGDIView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "GDI.h"
#endif

#include "GDIDoc.h"
#include "GDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGDIView

IMPLEMENT_DYNCREATE(CGDIView, CView)

BEGIN_MESSAGE_MAP(CGDIView, CView)
END_MESSAGE_MAP()

// CGDIView ����/����

CGDIView::CGDIView()
{
	// TODO: �ڴ˴���ӹ������

}

CGDIView::~CGDIView()
{
}

BOOL CGDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CGDIView ����

void CGDIView::OnDraw(CDC* pDC)
{
	CGDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	
	CString str("GDI Map Mode");
	CRect rect(0, 0, 300, 400);

	pDC->SetMapMode(MM_HIMETRIC);
	pDC->SetViewportOrg(100, 100);
	pDC->DrawText(str, &rect, 0);
	pDC->MoveTo(100, -1000);
	pDC->LineTo(300, -4000);
}


// CGDIView ���

#ifdef _DEBUG
void CGDIView::AssertValid() const
{
	CView::AssertValid();
}

void CGDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGDIDoc* CGDIView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGDIDoc)));
	return (CGDIDoc*)m_pDocument;
}
#endif //_DEBUG


// CGDIView ��Ϣ�������
