
// HexDumpDoc.cpp : CHexDumpDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "HexDump.h"
#endif

#include "HexDumpDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CHexDumpDoc

IMPLEMENT_DYNCREATE(CHexDumpDoc, CDocument)

BEGIN_MESSAGE_MAP(CHexDumpDoc, CDocument)
END_MESSAGE_MAP()


// CHexDumpDoc 构造/析构

CHexDumpDoc::CHexDumpDoc()
{
	// TODO: 在此添加一次性构造代码
	m_pFileData = NULL;
	m_nDocLength = 0;
}

CHexDumpDoc::~CHexDumpDoc()
{
}

UINT CHexDumpDoc::GetBytes(UINT nIndex, UINT nCount, PVOID pBuffer)
{
	if (nIndex >= m_nDocLength)
	{
		return 0;
	}

	UINT nLength = nCount;
	if ((nIndex + nCount) > m_nDocLength)
	{
		nLength = m_nDocLength - nIndex;
	}

	::CopyMemory(pBuffer, m_pFileData + nIndex, nLength);
	return nLength;
}

UINT CHexDumpDoc::GetDocumentLength()
{
	return m_nDocLength;
}

BOOL CHexDumpDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CHexDumpDoc 序列化

void CHexDumpDoc::Serialize(CArchive& ar)
{
	if (ar.IsLoading())
	{
		// TODO: 在此添加存储代码
		CFile* pFile = ar.GetFile();
		m_nDocLength = (UINT)pFile->GetLength();

		// Allocate a buffer for the file data
		try
		{
			m_pFileData = new BYTE[m_nDocLength];
		}
		catch (CMemoryException* e)
		{
			m_nDocLength = 0;
			throw e;
		}

		// Read the file data into the buffer
		try
		{
			pFile->Read(m_pFileData, m_nDocLength);
		}
		catch (CFileException* e)
		{
			delete[] m_pFileData;
			m_pFileData = NULL;
			m_nDocLength = 0;
			throw e;
		}
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

void CHexDumpDoc::DeleteContents()
{
	CDocument::DeleteContents();
	if (m_pFileData != NULL)
	{
		delete[] m_pFileData;
		m_pFileData = NULL;
		m_nDocLength = 0;
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CHexDumpDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CHexDumpDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CHexDumpDoc::SetSearchContent(const CString& value)
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

// CHexDumpDoc 诊断

#ifdef _DEBUG
void CHexDumpDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHexDumpDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CHexDumpDoc 命令
