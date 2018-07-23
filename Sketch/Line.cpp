
#include "stdafx.h"
#include "Sketch.h"
#include "Line.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLine
IMPLEMENT_SERIAL(CLine, CCmdTarget, 1)
// IMPLEMENT_DYNCREATE(CLine, CCmdTarget)

CLine::CLine()
{

}

CLine::CLine(POINT from, POINT to)
{
	m_ptFrom = from;
	m_ptTo = to;
}

BEGIN_MESSAGE_MAP(CLine, CCmdTarget)
END_MESSAGE_MAP()

void CLine::Draw(CDC* pDC)
{
	pDC->SelectStockObject(BLACK_PEN);
	pDC->MoveTo(m_ptFrom);
	pDC->LineTo(m_ptTo);
}

CLine::~CLine()
{

}

void CLine::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_ptFrom << m_ptTo;
	}
	else
	{
		ar >> m_ptFrom >> m_ptTo;
	}
}
