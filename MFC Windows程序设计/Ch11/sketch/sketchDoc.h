
// sketchDoc.h : CsketchDoc ��Ľӿ�
//


#pragma once

class CLine;

typedef CTypedPtrArray<CObArray, CLine*>	CLineArray;

class CsketchDoc : public CDocument
{
protected: // �������л�����
	CsketchDoc();
	DECLARE_DYNCREATE(CsketchDoc)

// ����
public:

// ����
public:

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
	virtual ~CsketchDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnViewGrid();
	afx_msg void OnUpdateViewGrid(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
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
