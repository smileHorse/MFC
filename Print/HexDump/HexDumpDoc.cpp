
// HexDumpDoc.cpp : CHexDumpDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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


// CHexDumpDoc ����/����

CHexDumpDoc::CHexDumpDoc()
{
	// TODO: �ڴ����һ���Թ������
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

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CHexDumpDoc ���л�

void CHexDumpDoc::Serialize(CArchive& ar)
{
	if (ar.IsLoading())
	{
		// TODO: �ڴ���Ӵ洢����
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
		// TODO: �ڴ���Ӽ��ش���
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

// ����ͼ��֧��
void CHexDumpDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
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

// ������������֧��
void CHexDumpDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:     strSearchContent = _T("point;rectangle;circle;ole object;")��
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

// CHexDumpDoc ���

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


// CHexDumpDoc ����
