
// ChildView.cpp : CChildView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "GridDemo.h"
#endif

#include "ChildView.h"
#include "SettingsDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_OPTIONS_GRID_SETTINGS, OnOptionsGridSettings)
END_MESSAGE_MAP()

// CChildView ����/����

CChildView::CChildView()
{
	m_cx = 8;
	m_cy = 8;
	m_nWeight = 4;
}

CChildView::~CChildView()
{
}

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
	{
		return FALSE;
	}

	cs.dwExStyle != WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS, ::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CRect rect;
	GetClientRect (&rect);

	int nShade = m_nWeight * 32;
	if (nShade != 0)
		nShade--;

	CPaintDC dc (this);
	CPen pen (PS_SOLID, 1, RGB (nShade, nShade, nShade));
	CPen* pOldPen = dc.SelectObject (&pen);

	int x;
	for (int i=1; i<m_cx; i++) {
		x = (rect.Width () * i) / m_cx;
		dc.MoveTo (x, 0);
		dc.LineTo (x, rect.Height ());
	}

	int y;
	for (int i=1; i<m_cy; i++) {
		y = (rect.Height () * i) / m_cy;
		dc.MoveTo (0, y);
		dc.LineTo (rect.Width (), y);
	}

	dc.SelectObject (pOldPen);
}

void CChildView::OnOptionsGridSettings() 
{
	CSettingDialog dlg;

	dlg.m_cx = m_cx;
	dlg.m_cy = m_cy;
	dlg.m_nWeight = m_nWeight;

	if (dlg.DoModal () == IDOK) {
		m_cx = dlg.m_cx;
		m_cy = dlg.m_cy;
		m_nWeight = dlg.m_nWeight;
		Invalidate ();
	}
}

