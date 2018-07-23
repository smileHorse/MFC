
#include "TabView.h"

IMPLEMENT_DYNCREATE(CTabView, CCtrlView)

BOOL CTabView::PreCreateWindow(CREATESTRUCT& cs)
{
	::InitCommonControls();
	if (!CCtrlView::PreCreateWindow(cs))
	{
		return FALSE;
	}
	cs.style |= TCS_FIXEDWIDTH;	// Fixed-width tabs
	return TRUE;
}

void CTabView::OnInitialUpdate()
{
	static CString strLabel[] = {_T("Tab No.1"), _T("Tab No.2"), _T("Tab No.3")};
	// Set the tab width to 96 pixels
	GetTabCtrl().SetItemSize(CSize(96, 0));
	// Add three tabs
	TC_ITEM item;
	item.mask = TCIF_TEXT;
	for (int i = 0; i < 3; i++)
	{
		item.pszText = (LPTSTR)(LPCTSTR)strLabel[i];
		item.cchTextMax = strLabel[i].GetLength();
		GetTabCtrl().InsertItem(i, &item);
	}
}