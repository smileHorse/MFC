
// MdiSquaresView.h : CMdiSquaresView ��Ľӿ�
//

#pragma once


class CMdiSquaresView : public CView
{
protected: // �������л�����
	CMdiSquaresView();
	DECLARE_DYNCREATE(CMdiSquaresView)

// ����
public:
	CMdiSquaresDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CMdiSquaresView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MdiSquaresView.cpp �еĵ��԰汾
inline CMdiSquaresDoc* CMdiSquaresView::GetDocument() const
   { return reinterpret_cast<CMdiSquaresDoc*>(m_pDocument); }
#endif

