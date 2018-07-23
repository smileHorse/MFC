
// DriveView.h : CDriveView 类的接口
//

#pragma once


class CDriveView : public CTreeView
{
protected: // 仅从序列化创建
	CDriveView();
	DECLARE_DYNCREATE(CDriveView)

// 特性
public:
	CWandererDoc* GetDocument() const;

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
	virtual ~CDriveView();
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
	afx_msg void OnSelectionChanged(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // DriveView.cpp 中的调试版本
inline CWandererDoc* CDriveView::GetDocument() const
   { return reinterpret_cast<CWandererDoc*>(m_pDocument); }
#endif

