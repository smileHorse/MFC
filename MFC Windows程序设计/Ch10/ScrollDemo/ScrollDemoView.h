
// ScrollDemoView.h : CScrollDemoView ��Ľӿ�
//

#pragma once


class CScrollDemoView : public CScrollView
{
protected: // �������л�����
	CScrollDemoView();
	DECLARE_DYNCREATE(CScrollDemoView)

// ����
public:
	CScrollDemoDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CScrollDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	BOOL m_bSmooth;
	void GetCellRect(int row, int col, LPRECT pRect);
	void DrawAddress(CDC* pDC, int row, int col);
	void DrawPointer(CDC* pDC, int row, int col, BOOL bHighlight);
	CFont m_font;
	int m_nCurrentCol;
	int m_nCurrentRow;
	int m_nRibbonWidth;
	int m_nCellHeight;
	int m_nCellWidth;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // ScrollDemoView.cpp �еĵ��԰汾
inline CScrollDemoDoc* CScrollDemoView::GetDocument() const
   { return reinterpret_cast<CScrollDemoDoc*>(m_pDocument); }
#endif

