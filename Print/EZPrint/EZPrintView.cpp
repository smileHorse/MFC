
// EZPrintView.cpp : CEZPrintView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "EZPrint.h"
#endif

#include "EZPrintDoc.h"
#include "EZPrintView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEZPrintView

IMPLEMENT_DYNCREATE(CEZPrintView, CView)

BEGIN_MESSAGE_MAP(CEZPrintView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEZPrintView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CEZPrintView ����/����

CEZPrintView::CEZPrintView()
{
	// TODO: �ڴ˴���ӹ������

}

CEZPrintView::~CEZPrintView()
{
}

BOOL CEZPrintView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CEZPrintView ����

void CEZPrintView::OnDraw(CDC* pDC)
{
	CEZPrintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	//CPen pen(PS_SOLID, 50, RGB(0, 0, 255));
	//CBrush brush(RGB(255, 255, 0));

	// ��ӡ��Ϊ�ڰ�ģʽʱ����ӡԤ���ͻ��ûҶ���Ⱦ
	// pDC->GetDeviceCaps(NUMCOLORS)����2��˵���ǵ�ɫ��ӡ��
	// RGB��ɫתΪ��ɫ���Ĺ�ʽΪ�� r/g/b = (red * 0.30) + (green * 0.59) + (blue * 0.11);
	BOOL bMono = (pDC->GetDeviceCaps(NUMCOLORS) == 2) &&
		(pDC->m_hDC != pDC->m_hAttribDC);
	CPen pen(PS_SOLID, 50, bMono ? RGB(28, 28, 28) : RGB(0, 0, 255));
	CBrush brush(bMono ? RGB(227, 227, 227) : RGB(255, 255, 0));


	pDC->SetMapMode(MM_LOMETRIC);
	CPen* pOldPen = pDC->SelectObject(&pen);
	CBrush* pOldBrush = pDC->SelectObject(&brush);

	pDC->Ellipse(100, -100, 1100, -1100);

	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
}


// CEZPrintView ��ӡ


void CEZPrintView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CEZPrintView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CEZPrintView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CEZPrintView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CEZPrintView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CEZPrintView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CEZPrintView ���

#ifdef _DEBUG
void CEZPrintView::AssertValid() const
{
	CView::AssertValid();
}

void CEZPrintView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEZPrintDoc* CEZPrintView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEZPrintDoc)));
	return (CEZPrintDoc*)m_pDocument;
}
#endif //_DEBUG


// CEZPrintView ��Ϣ�������
