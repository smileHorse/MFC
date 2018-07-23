
// SketchDoc.cpp : CSketchDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Sketch.h"
#endif

#include "Line.h"
#include "SketchDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSketchDoc

IMPLEMENT_DYNCREATE(CSketchDoc, CDocument)

BEGIN_MESSAGE_MAP(CSketchDoc, CDocument)
	ON_COMMAND(ID_VIEW_GRID, OnViewGrid)
	ON_UPDATE_COMMAND_UI(ID_VIEW_GRID, OnUpdateViewGrid)
END_MESSAGE_MAP()


// CSketchDoc 构造/析构

CSketchDoc::CSketchDoc()
{
	// TODO: 在此添加一次性构造代码

}

CLine* CSketchDoc::GetLine(int nIndex)
{
	ASSERT(nIndex < GetLineCount());
	return m_arrLines[nIndex];
}

int CSketchDoc::GetLineCount()
{
	return m_arrLines.GetSize();
}

CLine* CSketchDoc::AddLine(POINT from, POINT to)
{
	CLine* pLine = NULL;
	try
	{
		pLine = new CLine(from, to);
		m_arrLines.Add(pLine);
		SetModifiedFlag(TRUE);
		UpdateAllViews(NULL, 0x7C, pLine);
	}
	catch (CMemoryException* e)
	{
		AfxMessageBox(_T("Out of memory"));
		if (pLine != NULL)
		{
			delete pLine;
			pLine = NULL;
		}
		e->Delete();
	}
	return pLine;
}

BOOL CSketchDoc::IsGridVisible()
{
	return m_bShowGrid;
}

CSketchDoc::~CSketchDoc()
{
}

BOOL CSketchDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)
	m_bShowGrid = TRUE;

	return TRUE;
}




// CSketchDoc 序列化

void CSketchDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
		ar << m_bShowGrid;
	}
	else
	{
		// TODO: 在此添加加载代码
		ar >> m_bShowGrid;
	}
	m_arrLines.Serialize(ar);
}

void CSketchDoc::DeleteContents()
{
	int nCount = GetLineCount();
	if (nCount)
	{
		for (int i = 0; i < nCount; i++)
		{
			delete m_arrLines[i];
		}
		m_arrLines.RemoveAll();
	}
	CDocument::DeleteContents();
}

void CSketchDoc::OnViewGrid()
{
	if (m_bShowGrid)
	{
		m_bShowGrid = FALSE;
	}
	else
	{
		m_bShowGrid = TRUE;
	}

	SetModifiedFlag(TRUE);
	UpdateAllViews(NULL);
}

void CSketchDoc::OnUpdateViewGrid(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bShowGrid);
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CSketchDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CSketchDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CSketchDoc::SetSearchContent(const CString& value)
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

// CSketchDoc 诊断

#ifdef _DEBUG
void CSketchDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSketchDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSketchDoc 命令
