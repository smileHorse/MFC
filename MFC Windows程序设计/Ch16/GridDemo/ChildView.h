
// ChildView.h : CChildView 类的接口
//

#pragma once


class CChildView : public CWnd
{
public: // 仅从序列化创建
	CChildView();

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CChildView();

protected:

// 生成的消息映射函数
protected:
	int m_nWeight;
	int m_cy;
	int m_cx;

	afx_msg void OnPaint();
	afx_msg void OnOptionsGridSettings();
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // ChildView.cpp 中的调试版本
inline CGridDemoDoc* CChildView::GetDocument() const
   { return reinterpret_cast<CGridDemoDoc*>(m_pDocument); }
#endif

