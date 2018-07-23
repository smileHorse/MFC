
// HexDumpDoc.h : CHexDumpDoc ��Ľӿ�
//


#pragma once


class CHexDumpDoc : public CDocument
{
protected: // �������л�����
	CHexDumpDoc();
	DECLARE_DYNCREATE(CHexDumpDoc)

// ����
public:

// ����
public:
	UINT GetBytes(UINT nIndex, UINT nCount, PVOID pBuffer);
	UINT GetDocumentLength();

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CHexDumpDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	BYTE* m_pFileData;
	UINT m_nDocLength;

	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
