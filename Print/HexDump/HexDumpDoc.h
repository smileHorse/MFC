
// HexDumpDoc.h : CHexDumpDoc 类的接口
//


#pragma once


class CHexDumpDoc : public CDocument
{
protected: // 仅从序列化创建
	CHexDumpDoc();
	DECLARE_DYNCREATE(CHexDumpDoc)

// 特性
public:

// 操作
public:
	UINT GetBytes(UINT nIndex, UINT nCount, PVOID pBuffer);
	UINT GetDocumentLength();

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CHexDumpDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	BYTE* m_pFileData;
	UINT m_nDocLength;

	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
