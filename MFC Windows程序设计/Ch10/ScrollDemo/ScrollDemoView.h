
// ScrollDemoView.h : CScrollDemoView 类的接口
//

#pragma once


class CScrollDemoView : public CScrollView
{
protected: // 仅从序列化创建
	CScrollDemoView();
	DECLARE_DYNCREATE(CScrollDemoView)

// 特性
public:
	CScrollDemoDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CScrollDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // ScrollDemoView.cpp 中的调试版本
inline CScrollDemoDoc* CScrollDemoView::GetDocument() const
   { return reinterpret_cast<CScrollDemoDoc*>(m_pDocument); }
#endif

