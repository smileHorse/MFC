
// ImageEditView.h : CImageEditView 类的接口
//

#pragma once


class CImageEditView : public CScrollView
{
protected: // 仅从序列化创建
	CImageEditView();
	DECLARE_DYNCREATE(CImageEditView)

// 特性
public:
	CImageEditDoc* GetDocument() const;

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
	virtual ~CImageEditView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // ImageEditView.cpp 中的调试版本
inline CImageEditDoc* CImageEditView::GetDocument() const
   { return reinterpret_cast<CImageEditDoc*>(m_pDocument); }
#endif

