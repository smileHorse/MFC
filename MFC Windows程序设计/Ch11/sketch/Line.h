#pragma once

class CLine : public CCmdTarget
{
	DECLARE_SERIAL(CLine)

	CLine();
	CLine(POINT from, POINT to);

public:
	void Draw(CDC* pDC);
	virtual ~CLine();

public:
	virtual void Serialize(CArchive& ar);

protected:
	CPoint m_ptFrom;
	CPoint m_ptTo;

	DECLARE_MESSAGE_MAP()
};