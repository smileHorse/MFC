
// MdiSquaresView.h : CMdiSquaresView 类的接口
//

#pragma once


class CMdiSquaresView : public CView
{
protected: // 仅从序列化创建
	CMdiSquaresView();
	DECLARE_DYNCREATE(CMdiSquaresView)

// 特性
public:
	CMdiSquaresDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CMdiSquaresView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MdiSquaresView.cpp 中的调试版本
inline CMdiSquaresDoc* CMdiSquaresView::GetDocument() const
   { return reinterpret_cast<CMdiSquaresDoc*>(m_pDocument); }
#endif

