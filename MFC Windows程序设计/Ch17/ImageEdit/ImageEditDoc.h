
// ImageEditDoc.h : CImageEditDoc ��Ľӿ�
//


#pragma once


class CImageEditDoc : public CDocument
{
protected: // �������л�����
	CImageEditDoc();
	DECLARE_DYNCREATE(CImageEditDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void DeleteContents();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
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

// ���ɵ���Ϣӳ�亯��
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
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
