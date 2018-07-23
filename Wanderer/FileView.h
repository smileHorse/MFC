
// FileView.h : CFileView ��Ľӿ�
//

#pragma once

typedef struct tagITEMINFO
{
	CString strFileName;
	DWORD nFileSizeLow;
	FILETIME ftLastWriteTime;
} ITEMINFO;

class CFileView : public CListView
{
protected: // �������л�����
	CFileView();
	DECLARE_DYNCREATE(CFileView)

// ����
public:
	CWandererDoc* GetDocument() const;

// ����
public:
	static int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

// ��д
public:
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);

// ʵ��
public:
	virtual ~CFileView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	int Refresh(LPCTSTR pszPath);

protected:
	CString m_strPath;
	void FreeItemMemory();
	BOOL AddItem(int nIndex, WIN32_FIND_DATA* pfd);
	CImageList m_ilSmall;
	CImageList m_ilLarge;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnDestroy();
	afx_msg void OnGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnViewLargeIcons();
	afx_msg void OnViewSmallIcons();
	afx_msg void OnViewList();
	afx_msg void OnViewDetails();
	afx_msg void OnUpdateViewLargeIcons(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewSmallIcons(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewList(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewDetails(CCmdUI* pCmdUI);
	afx_msg void OnFileNewDirectory();
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // FileView.cpp �еĵ��԰汾
inline CWinDirDoc* CFileView::GetDocument() const
   { return reinterpret_cast<CWinDirDoc*>(m_pDocument); }
#endif

