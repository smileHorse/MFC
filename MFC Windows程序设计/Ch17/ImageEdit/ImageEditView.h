
// ImageEditView.h : CImageEditView ��Ľӿ�
//

#pragma once


class CImageEditView : public CScrollView
{
protected: // �������л�����
	CImageEditView();
	DECLARE_DYNCREATE(CImageEditView)

// ����
public:
	CImageEditDoc* GetDocument() const;

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
	virtual ~CImageEditView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // ImageEditView.cpp �еĵ��԰汾
inline CImageEditDoc* CImageEditView::GetDocument() const
   { return reinterpret_cast<CImageEditDoc*>(m_pDocument); }
#endif

