
// ImageEditDoc.h : CImageEditDoc 类的接口
//


#pragma once


class CImageEditDoc : public CDocument
{
protected: // 仅从序列化创建
	CImageEditDoc();
	DECLARE_DYNCREATE(CImageEditDoc)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void DeleteContents();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	void ThreadAborted();
	void ThreadFinished();
	CPalette* GetPalette();
	CBitmap* GetBitmap();
	virtual ~CImageEditDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	CCriticalSection m_cs;
	CEvent m_event;
	HANDLE m_hThread;
	BOOL m_bWorking;
	CPalette m_palette;
	CBitmap m_bitmap;

	afx_msg void OnGrayScale();
	afx_msg void OnUpdateGrayScale(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
