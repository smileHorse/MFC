
// ChildView.h : CChildView ��Ľӿ�
//

#pragma once


class CChildView : public CWnd
{
public: // �������л�����
	CChildView();

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CChildView();

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	int m_nWeight;
	int m_cy;
	int m_cx;

	afx_msg void OnPaint();
	afx_msg void OnOptionsGridSettings();
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // ChildView.cpp �еĵ��԰汾
inline CGridDemoDoc* CChildView::GetDocument() const
   { return reinterpret_cast<CGridDemoDoc*>(m_pDocument); }
#endif

