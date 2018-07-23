
// GDIView.h : CGDIView ��Ľӿ�
//

#pragma once


class CGDIView : public CView
{
protected: // �������л�����
	CGDIView();
	DECLARE_DYNCREATE(CGDIView)

// ����
public:
	CGDIDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CGDIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // GDIView.cpp �еĵ��԰汾
inline CGDIDoc* CGDIView::GetDocument() const
   { return reinterpret_cast<CGDIDoc*>(m_pDocument); }
#endif

