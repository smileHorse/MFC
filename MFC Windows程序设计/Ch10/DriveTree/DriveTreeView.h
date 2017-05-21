
// DriveTreeView.h : CDriveTreeView ��Ľӿ�
//

#pragma once


class CDriveTreeView : public CTreeView
{
protected: // �������л�����
	CDriveTreeView();
	DECLARE_DYNCREATE(CDriveTreeView)

// ����
public:
	CDriveTreeDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CDriveTreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	BOOL AddDriveItem(LPCTSTR pszDrive);
	int AddDirectories(HTREEITEM hItem, LPCTSTR pszPath);
	void DeleteAllChildren(HTREEITEM hItem);
	void DeleteFirstChild(HTREEITEM hItem);
	CString GetPathFromItem(HTREEITEM hItem);
	BOOL SetButtonState(HTREEITEM hItem, LPCTSTR pszPath);
	int AddDrives();
	CImageList m_ilDrives;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnItemExpanding(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // DriveTreeView.cpp �еĵ��԰汾
inline CDriveTreeDoc* CDriveTreeView::GetDocument() const
   { return reinterpret_cast<CDriveTreeDoc*>(m_pDocument); }
#endif

