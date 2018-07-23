
// DriveViewView.h : CDriveViewView ��Ľӿ�
//

#pragma once


class CDriveViewView : public CTreeView
{
protected: // �������л�����
	CDriveViewView();
	DECLARE_DYNCREATE(CDriveViewView)

// ����
public:
	CDriveViewDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate();

// ʵ��
public:
	virtual ~CDriveViewView();
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

#ifndef _DEBUG  // DriveViewView.cpp �еĵ��԰汾
inline CDriveViewDoc* CDriveViewView::GetDocument() const
   { return reinterpret_cast<CDriveViewDoc*>(m_pDocument); }
#endif

