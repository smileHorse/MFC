
// DriveTreeView.h : CDriveTreeView 类的接口
//

#pragma once


class CDriveTreeView : public CTreeView
{
protected: // 仅从序列化创建
	CDriveTreeView();
	DECLARE_DYNCREATE(CDriveTreeView)

// 特性
public:
	CDriveTreeDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
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

// 生成的消息映射函数
protected:
	afx_msg void OnItemExpanding(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // DriveTreeView.cpp 中的调试版本
inline CDriveTreeDoc* CDriveTreeView::GetDocument() const
   { return reinterpret_cast<CDriveTreeDoc*>(m_pDocument); }
#endif

