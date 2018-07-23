#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Line.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLine command target

class CLine : public CCmdTarget
{
	DECLARE_SERIAL(CLine)
	/*DECLARE_DYNCREATE(CLine)*/

	CLine();
	CLine(POINT from, POINT to);

public:
	void Draw(CDC* pDC);
	virtual ~CLine();

	virtual void Serialize(CArchive& ar);

protected:
	CPoint m_ptFrom;
	CPoint m_ptTo;

	// Generated message map functions
	//{{AFX_MSG(CLine)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

};