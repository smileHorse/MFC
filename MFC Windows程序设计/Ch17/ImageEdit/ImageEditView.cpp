
// ImageEditView.cpp : CImageEditView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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

// CImageEditView ����/����

CImageEditView::CImageEditView()
{
	// TODO: �ڴ˴���ӹ������

}

CImageEditView::~CImageEditView()
{
}

BOOL CImageEditView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CScrollView::PreCreateWindow(cs);
}

// CImageEditView ����

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


// CImageEditView ���

#ifdef _DEBUG
void CImageEditView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImageEditView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImageEditDoc* CImageEditView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageEditDoc)));
	return (CImageEditDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageEditView ��Ϣ�������
