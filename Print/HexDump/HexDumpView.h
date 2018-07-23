
// HexDumpView.h : CHexDumpView ��Ľӿ�
//

#pragma once


class CHexDumpView : public CScrollView
{
protected: // �������л�����
	CHexDumpView();
	DECLARE_DYNCREATE(CHexDumpView)

// ����
public:
	CHexDumpDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate();
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CHexDumpView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void FormatLine(CHexDumpDoc* pDoc, UINT nLine, CString& string);
	void PrintPageHeader(CHexDumpDoc* pDoc, CDC* pDC, UINT nPageNumber);
	void PrintPage(CHexDumpDoc* pDoc, CDC* pDC, UINT nPageNumber);
	UINT m_cxWidth;
	UINT m_cxOffset;
	UINT m_nLinesPerPage;
	UINT m_nLinesTotal;
	UINT m_cyPrinter;
	UINT m_cyScreen;
	CFont m_fontPrinter;
	CFont m_fontScreen;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpcs);
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // HexDumpView.cpp �еĵ��԰汾
inline CHexDumpDoc* CHexDumpView::GetDocument() const
   { return reinterpret_cast<CHexDumpDoc*>(m_pDocument); }
#endif

