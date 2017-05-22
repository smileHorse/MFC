
// sketchDoc.h : CsketchDoc 类的接口
//


#pragma once

class CLine;

typedef CTypedPtrArray<CObArray, CLine*>	CLineArray;

class CsketchDoc : public CDocument
{
protected: // 仅从序列化创建
	CsketchDoc();
	DECLARE_DYNCREATE(CsketchDoc)

// 特性
public:

// 操作
public:

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
	virtual ~CsketchDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnViewGrid();
	afx_msg void OnUpdateViewGrid(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

public:
	CLine* GetLine(int nIndex);
	int GetLineCount();
	CLine* AddLine(POINT from, POINT to);
	BOOL IsGridVisible();

protected:
	CLineArray m_arrLines;
	BOOL	m_bShowGrid;
};
