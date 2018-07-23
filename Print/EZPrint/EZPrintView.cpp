
// EZPrintView.cpp : CEZPrintView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEZPrintView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CEZPrintView 构造/析构

CEZPrintView::CEZPrintView()
{
	// TODO: 在此处添加构造代码

}

CEZPrintView::~CEZPrintView()
{
}

BOOL CEZPrintView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CEZPrintView 绘制

void CEZPrintView::OnDraw(CDC* pDC)
{
	CEZPrintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	//CPen pen(PS_SOLID, 50, RGB(0, 0, 255));
	//CBrush brush(RGB(255, 255, 0));

	// 打印机为黑白模式时，打印预览就会用灰度渲染
	// pDC->GetDeviceCaps(NUMCOLORS)返回2，说明是单色打印机
	// RGB颜色转为灰色调的公式为： r/g/b = (red * 0.30) + (green * 0.59) + (blue * 0.11);
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


// CEZPrintView 打印


void CEZPrintView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CEZPrintView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CEZPrintView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CEZPrintView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
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


// CEZPrintView 诊断

#ifdef _DEBUG
void CEZPrintView::AssertValid() const
{
	CView::AssertValid();
}

void CEZPrintView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEZPrintDoc* CEZPrintView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEZPrintDoc)));
	return (CEZPrintDoc*)m_pDocument;
}
#endif //_DEBUG


// CEZPrintView 消息处理程序
