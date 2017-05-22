
// sketchView.h : CsketchView ��Ľӿ�
//

#pragma once


class CsketchView : public CScrollView
{
protected: // �������л�����
	CsketchView();
	DECLARE_DYNCREATE(CsketchView)

// ����
public:
	CsketchDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	virtual void OnInitialUpdate();
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);

// ʵ��
public:
	virtual ~CsketchView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	void InvertLine(CDC* pDC, POINT from, POINT to);
	CPoint m_ptFrom;
	CPoint m_ptTo;
	HCURSOR m_hCursor;

	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // sketchView.cpp �еĵ��԰汾
inline CsketchDoc* CsketchView::GetDocument() const
   { return reinterpret_cast<CsketchDoc*>(m_pDocument); }
#endif

