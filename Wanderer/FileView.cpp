
// FileView.cpp : CFileView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Wanderer.h"
#endif

#include "WandererDoc.h"
#include "FileView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFileView

IMPLEMENT_DYNCREATE(CFileView, CListView)

BEGIN_MESSAGE_MAP(CFileView, CListView)
	ON_WM_DESTROY()
	ON_NOTIFY_REFLECT(LVN_GETDISPINFO, OnGetDispInfo)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnClick)
	ON_COMMAND(ID_VIEW_LARGE_ICONS, OnViewLargeIcons)
	ON_COMMAND(ID_VIEW_SMALL_ICONS, OnViewSmallIcons)
	ON_COMMAND(ID_VIEW_LIST, OnViewList)
	ON_COMMAND(ID_VIEW_DETAILS, OnViewDetails)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LARGE_ICONS, OnUpdateViewLargeIcons)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SMALL_ICONS, OnUpdateViewSmallIcons)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LIST, OnUpdateViewList)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DETAILS, OnUpdateViewDetails)
END_MESSAGE_MAP()

// CFileView 构造/析构

CFileView::CFileView()
{
	// TODO: 在此处添加构造代码

}

CFileView::~CFileView()
{
}

BOOL CFileView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	if (!CListView::PreCreateWindow(cs))
	{
		return FALSE;
	}

	cs.style &= ~LVS_TYPEMASK;
	cs.style |= LVS_REPORT;
	return TRUE;
}

void CFileView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// TODO: 调用 GetListCtrl() 直接访问 ListView 的列表控件，
	//  从而可以用项填充 ListView。
	
	// Initialize the image list
	m_ilLarge.Create(IDB_LARGEDOCS, 32, 1, RGB(255, 0, 255));
	m_ilSmall.Create(IDB_SMALLDOCS, 16, 1, RGB(255, 0, 255));

	GetListCtrl().SetImageList(&m_ilLarge, LVSIL_NORMAL);
	GetListCtrl().SetImageList(&m_ilSmall, LVSIL_SMALL);

	// Add columns to the list view
	GetListCtrl().InsertColumn(0, _T("File Name"), LVCFMT_LEFT, 192);
	GetListCtrl().InsertColumn(1, _T("Size"), LVCFMT_RIGHT, 96);
	GetListCtrl().InsertColumn(2, _T("Last Modified"), LVCFMT_CENTER, 128);

	// Populate the list view with items
	TCHAR szPath[MAX_PATH];
	::GetCurrentDirectory(sizeof(szPath) / sizeof(TCHAR), szPath);
	Refresh(szPath);
}


void CFileView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	if (lHint == 0x5A)
	{
		FreeItemMemory();
		GetListCtrl().DeleteAllItems();
		Refresh((LPCTSTR)pHint);
		return;
	}
	CListView::OnUpdate(pSender, lHint, pHint);
}

// CFileView 诊断

#ifdef _DEBUG
void CFileView::AssertValid() const
{
	CListView::AssertValid();
}

void CFileView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

int CFileView::Refresh(LPCTSTR pszPath)
{
	CString strPath = pszPath;
	if (strPath.Right(1) != _T("\\"))
	{
		strPath += _T("\\");
	}
	strPath += _T("*.*");

	HANDLE hFind;
	WIN32_FIND_DATA fd;
	int nCount = 0;

	if ((hFind = ::FindFirstFile(strPath, &fd)) != INVALID_HANDLE_VALUE)
	{
		// Delete existing items(if any)
		GetListCtrl().DeleteAllItems();

		// Show the path name in the frame window's title bar
		TCHAR szFullPath[MAX_PATH];
		::GetFullPathName(pszPath, sizeof(szFullPath) / sizeof(TCHAR), szFullPath, NULL);
		m_strPath = pszPath;

		CString strTitle = _T("WinDir - ");
		strTitle += m_strPath;
		AfxGetMainWnd()->SetWindowTextW(strTitle);

		// Add items representing files to the list view
		if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			AddItem(nCount++, &fd);
		}
		while (::FindNextFile(hFind, &fd))
		{
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				if (!AddItem(nCount++, &fd))
				{
					break;
				}
			}
		}
		::FindClose(hFind);
	}
	return nCount;
}

void CFileView::FreeItemMemory()
{
	int nCount = GetListCtrl().GetItemCount();
	if (nCount)
	{
		for (int i = 0; i < nCount; i++)
		{
			delete (ITEMINFO*)GetListCtrl().GetItemData(i);
		}
	}
}

BOOL CFileView::AddItem(int nIndex, WIN32_FIND_DATA* pfd)
{
	// Allocate a new ITEMINFO structure and initialize it with information about the item
	ITEMINFO* pItem;
	try
	{
		pItem = new ITEMINFO;
	}
	catch (CMemoryException* e)
	{
		e->Delete();
		return FALSE;
	}

	pItem->strFileName = pfd->cFileName;
	pItem->nFileSizeLow = pfd->nFileSizeLow;
	pItem->ftLastWriteTime = pfd->ftLastWriteTime;

	// Add the item to the list view
	LV_ITEM lvi;
	lvi.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
	lvi.iItem = nIndex;
	lvi.iSubItem = 0;
	lvi.iImage = 0;
	lvi.pszText = LPSTR_TEXTCALLBACK;
	lvi.lParam = (LPARAM)pItem;
	if (GetListCtrl().InsertItem(&lvi) == -1)
	{
		return FALSE;
	}
	return TRUE;
}

void CFileView::OnDestroy()
{
	FreeItemMemory();
	CListView::OnDestroy();
}

void CFileView::OnGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult)
{
	CString string;
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;

	if (pDispInfo->item.mask & LVIF_TEXT)
	{
		ITEMINFO* pItem = (ITEMINFO*)pDispInfo->item.lParam;
		switch (pDispInfo->item.iSubItem)
		{
		case 0:	// File Name
		{
			::lstrcpy(pDispInfo->item.pszText, pItem->strFileName);
			break;
		}
		case 1:	// File Size
		{
			string.Format(_T("%u"), pItem->nFileSizeLow);
			::lstrcpy(pDispInfo->item.pszText, string);
			break;
		}
		case 2: // Date and time
		{
			CTime time(pItem->ftLastWriteTime);
			BOOL pm = FALSE;
			int nHour = time.GetHour();
			if (nHour == 0)
			{
				nHour = 12;
			}
			else if (nHour == 12)
			{
				pm = TRUE;
			}
			else if (nHour > 12)
			{
				nHour -= 12;
				pm = TRUE;
			}
			string.Format(_T("%d/%0.2d/%0.2d( %d:%0.2d%c)"),
				time.GetMonth(), time.GetDay(), time.GetYear() % 100,
				nHour, time.GetMinute(), pm ? _T('p') : _T('a'));
			::lstrcpy(pDispInfo->item.pszText, string);
			break;
		}
		default:
			break;
		}
	}
	*pResult = 0;
}

void CFileView::OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	GetListCtrl().SortItems(CompareFunc, pNMListView->iSubItem);
	*pResult = 0;
}

void CFileView::OnViewLargeIcons()
{
	ModifyStyle(LVS_TYPEMASK, LVS_ICON);
}

void CFileView::OnViewSmallIcons()
{
	ModifyStyle(LVS_TYPEMASK, LVS_SMALLICON);
}

void CFileView::OnViewList()
{
	ModifyStyle(LVS_TYPEMASK, LVS_LIST);
}

void CFileView::OnViewDetails()
{
	ModifyStyle(LVS_TYPEMASK, LVS_REPORT);
}

void CFileView::OnUpdateViewLargeIcons(CCmdUI* pCmdUI)
{
	DWORD dwCurrentStyle = GetStyle() & LVS_TYPEMASK;
	pCmdUI->SetRadio(dwCurrentStyle == LVS_ICON);
}

void CFileView::OnUpdateViewSmallIcons(CCmdUI* pCmdUI)
{
	DWORD dwCurrentStyle = GetStyle() & LVS_TYPEMASK;
	pCmdUI->SetRadio(dwCurrentStyle == LVS_SMALLICON);
}

void CFileView::OnUpdateViewList(CCmdUI* pCmdUI)
{
	DWORD dwCurrentStyle = GetStyle() & LVS_TYPEMASK;
	pCmdUI->SetRadio(dwCurrentStyle == LVS_LIST);
}

void CFileView::OnUpdateViewDetails(CCmdUI* pCmdUI)
{
	DWORD dwCurrentStyle = GetStyle() & LVS_TYPEMASK;
	pCmdUI->SetRadio(dwCurrentStyle == LVS_REPORT);
}

void CFileView::OnFileNewDirectory()
{
	//CPathDialog dlg;
	//dlg.m_strPath = m_strPath;
	//if (dlg.DoModal() == IDOK)
	//{
	//	Refresh(dlg.m_strPath);
	//}
}

CWandererDoc* CFileView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWandererDoc)));
	return (CWandererDoc*)m_pDocument;
}
#endif //_DEBUG


// CFileView 消息处理程序

int CALLBACK CFileView::CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	ITEMINFO* pItem1 = (ITEMINFO*)lParam1;
	ITEMINFO* pItem2 = (ITEMINFO*)lParam2;
	int nResult;

	switch (lParamSort)
	{
	case 0:	// File Name
		nResult = pItem1->strFileName.CompareNoCase(pItem2->strFileName);
		break;
	case 1:	// File Size
		nResult = pItem1->nFileSizeLow - pItem2->nFileSizeLow;
		break;
	case 2:	// Date and time
		nResult = ::CompareFileTime(&pItem1->ftLastWriteTime, &pItem2->ftLastWriteTime);
		break;
	default:
		break;
	}
	return nResult;
}

void CFileView::OnDraw(CDC* pDC)
{
	CWandererDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

