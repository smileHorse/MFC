
// DriveViewView.h : CDriveViewView 类的接口
//

#pragma once


class CDriveViewView : public CTreeView
{
protected: // 仅从序列化创建
	CDriveViewView();
	DECLARE_DYNCREATE(CDriveViewView)

// 特性
public:
	CDriveViewDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate();

// 实现
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

// 生成的消息映射函数
protected:
	afx_msg void OnItemExpanding(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // DriveViewView.cpp 中的调试版本
inline CDriveViewDoc* CDriveViewView::GetDocument() const
   { return reinterpret_cast<CDriveViewDoc*>(m_pDocument); }
#endif

