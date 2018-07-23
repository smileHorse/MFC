
// MdiSquaresDoc.cpp : CMdiSquaresDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MdiSquares.h"
#endif

#include "MdiSquaresDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMdiSquaresDoc

IMPLEMENT_DYNCREATE(CMdiSquaresDoc, CDocument)

BEGIN_MESSAGE_MAP(CMdiSquaresDoc, CDocument)
	ON_COMMAND(ID_COLOR_RED, OnColorRed)
	ON_COMMAND(ID_COLOR_YELLOW, OnColorYellow)
	ON_COMMAND(ID_COLOR_GREEN, OnColorGreen)
	ON_COMMAND(ID_COLOR_CYAN, OnColorCyan)
	ON_COMMAND(ID_COLOR_BLUE, OnColorBlue)
	ON_COMMAND(ID_COLOR_WHITE, OnColorWhite)
	ON_UPDATE_COMMAND_UI(ID_COLOR_RED, OnUpdateColorRed)
	ON_UPDATE_COMMAND_UI(ID_COLOR_YELLOW, OnUpdateColorYellow)
	ON_UPDATE_COMMAND_UI(ID_COLOR_GREEN, OnUpdateColorGreen)
	ON_UPDATE_COMMAND_UI(ID_COLOR_CYAN, OnUpdateColorCyan)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLUE, OnUpdateColorBlue)
	ON_UPDATE_COMMAND_UI(ID_COLOR_WHITE, OnUpdateColorWhite)
END_MESSAGE_MAP()


// CMdiSquaresDoc 构造/析构

CMdiSquaresDoc::CMdiSquaresDoc()
{
	// TODO: 在此添加一次性构造代码

}

void CMdiSquaresDoc::SetSquare(int i, int j, COLORREF color)
{
	ASSERT(i >= 0 && i < 4 && j >= 0 && j < 4);
	m_clrGrid[i][j] = color;
	SetModifiedFlag(TRUE);
	UpdateAllViews(NULL);
}

COLORREF CMdiSquaresDoc::GetSquare(int i, int j)
{
	ASSERT(i >= 0 && i < 4 && j >= 0 && j < 4);
	return m_clrGrid[i][j];
}

COLORREF CMdiSquaresDoc::GetCurrentColor()
{
	return m_clrCurrentColor;
}

CMdiSquaresDoc::~CMdiSquaresDoc()
{
}

BOOL CMdiSquaresDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m_clrGrid[i][j] = RGB(255, 255, 255);
		}
	}
	m_clrCurrentColor = RGB(255, 0, 0);

	return TRUE;
}




// CMdiSquaresDoc 序列化

void CMdiSquaresDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				ar << m_clrGrid[i][j];
			}
		}
		ar << m_clrCurrentColor;
	}
	else
	{
		// TODO: 在此添加加载代码
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				ar >> m_clrGrid[i][j];
			}
		}
		ar >> m_clrCurrentColor;
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CMdiSquaresDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CMdiSquaresDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CMdiSquaresDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMdiSquaresDoc 诊断

#ifdef _DEBUG
void CMdiSquaresDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMdiSquaresDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}

void CMdiSquaresDoc::OnColorRed()
{
	m_clrCurrentColor = RGB(255, 0, 0);
}

void CMdiSquaresDoc::OnColorYellow()
{
	m_clrCurrentColor = RGB(255, 255, 0);
}

void CMdiSquaresDoc::OnColorGreen()
{
	m_clrCurrentColor = RGB(0, 255, 0);
}

void CMdiSquaresDoc::OnColorCyan()
{
	m_clrCurrentColor = RGB(0, 255, 255);
}

void CMdiSquaresDoc::OnColorBlue()
{
	m_clrCurrentColor = RGB(0, 0, 255);
}

void CMdiSquaresDoc::OnColorWhite()
{
	m_clrCurrentColor = RGB(255, 255, 255);
}

void CMdiSquaresDoc::OnUpdateColorRed(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(m_clrCurrentColor == RGB(255, 0, 0));
}

void CMdiSquaresDoc::OnUpdateColorYellow(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(m_clrCurrentColor == RGB(255, 255, 0));
}

void CMdiSquaresDoc::OnUpdateColorGreen(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(m_clrCurrentColor == RGB(0, 255, 0));
}

void CMdiSquaresDoc::OnUpdateColorCyan(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(m_clrCurrentColor == RGB(0, 255, 255));
}

void CMdiSquaresDoc::OnUpdateColorBlue(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(m_clrCurrentColor == RGB(0, 0, 255));
}

void CMdiSquaresDoc::OnUpdateColorWhite(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(m_clrCurrentColor == RGB(255, 255, 255));
}

#endif //_DEBUG


// CMdiSquaresDoc 命令
